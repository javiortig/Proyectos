#!/bin/bash



# TODO: function to predict which team is going to win based on picks/bans, individual skill, champion skill and matchup synergy


#CONSTANT VARIAVLES
readonly SEASON_SEARCH=15   # const. to get data from player season's performance. 15=season_10
readonly MIN_GAMES_PLAYED=7   # const. for min games played required with each champion to compute performance


searchWinrate(){    

    # Looks for the closest champion result, checks if that name exists
    search_name=$( getClosestChampion ${1} )
    if [ $? -ne 0 ]; then
        echo "ERROR: invalid champion '${1}'"
        return 1
    fi

    # Looks for position, same idea as last code block
    search_position=$( getSearchPosition ${2} )
    if [ $? -ne 0 ]; then
        echo "ERROR: invalid position '${2}'"
        return 2
    fi

    response=$( curl -s  https://euw.op.gg/champion/${search_name}/statistics/${search_position}/trend | ./hxnormalize -x )

    win_rate=$( echo "${response}" | ./hxselect ".champion-stats-trend-rate" | egrep -o "[[:digit:]]+\.[[:digit:]]+%" | head -1 )

    # Checks if theres data aviable for the champion
    if [ -z "${win_rate}" ]; then
        echo "ERROR: there isn't enought data for ${search_name} ${search_position}"
        return 2
    fi

    if [ $3 = 'v' ];then
        echo -e "\e[93m${search_name}'s\e[0m winrate on \e[96m${search_position}\e[0m is \e[92m${win_rate}\e[0m"
    else
        echo "${win_rate}"
    fi

    return 0
}


getTierList(){
    response=$( curl -s https://mobalytics.gg/blog/lol-tier-list-for-climbing-solo-queue/ | ./hxnormalize -x | ./hxselect -c '.section' )

    x_roles=('jungle' 'mid' 'adc' 'support' 'NoneNone') # Array used to loop thorugh the
    roles=('Top' 'Jungle' 'MidLane' 'ADC' 'Support')

    echo ""
    for (( i=0; i<=4; i++ )); do  # Each iteration cuts with sed the portion we need for each role

        position=$( echo "${response}" | sed -e "/${x_roles[$i]}/q" )

        response=$( echo "${response/${position}/.}" )  # Deletes substring position from string response

        position=$( echo "${position}" | egrep -o "</img>[[:alpha:]]+</a>" | awk -F ">" '{print $2}' | awk -F "<" '{print $1}' | tr "\n" " " )
        echo -e "\e[96m${roles[$i]}\e[0m=\e[93m${position}\e[0m\n"
        
        
    done
}

getSearchPosition(){
    # Cleans search_position
    search_position=$( echo "$1" | tr -cd '[:alpha:]' | tr '[:upper:]' '[:lower:]' )
    case ${search_position} in  # Chooses between the possible 5 positions, accepting abbreviations
        "top"* ) 
        echo "top"
        ;;
        "j"*"g"*"l"* ) 
        echo "jungle"
        ;;
        "mid"* ) 
        echo "mid"
        ;;
        "bot"*|"adc" ) 
        echo "bot"
        ;;
        "sup"* ) 
        echo "support"
        ;;
        *)
        return 1
        ;;
        
    esac
}


getCounterList(){   # Shows best Champions to pick against the given champion as paratemer

    if [ "$1" = "-n" ] || [ "$1" = "--number" ];then 
        max_iterations=$2
        search_name=$3
        search_position=$4
    else
        max_iterations=10
        search_name=$1
        search_position=$2
    fi

    # Clean search_name
    search_name=$( echo "${search_name}" | tr -cd '[:alpha:]' | tr '[:upper:]' '[:lower:]' ) #Removes All non alphabetic characters and converts to lowercase
    search_name=$( getClosestChampion ${search_name} )
    if [ $? -ne 0 ]; then
        echo "ERROR: invalid champion name '${1}'" # If it hasnt found any matches, print and return error
        return 1
    fi

    # Gets the position top/mid/jungle/bot/support and its variants
    search_position=$( getSearchPosition ${search_position} )
    if [ $? -ne 0 ]; then
        echo "ERROR: invalid position"
        return 2
    fi

    response=$( curl -s https://euw.op.gg/champion/${search_name}/statistics/${search_position}/matchup | ./hxnormalize -x | ./hxselect '.champion-matchup-champion-list__item' | ./hxnormalize -x | awk '/champion-matchup-champion-list__item/,/>/' )

    if [ -z "${response}" ]; then   # If there is literally 0 data about the matchup
        echo "ERROR. There is not enought data for that matchup."
        return 3
    fi

    declare -a blocks

    i=0
    while true; do
        match=$( echo "${response}" | awk '/champion-matchup-champion-list__item/&&++k==1,/>/' ) # Get only first match

        if [ ${#match} -lt 2 ];then  # If we have treated all champions, leave loop
            break
        fi

        response=$( echo "${response/${match}/.}" )  # Deletes the iteration from the response

        name=$(  echo "${match}" | egrep -o "key=\".*\"" | awk -F "\"" '{print $2}' )
        win_rate=$( echo "${match}" | egrep -o "0\.[[:digit:]]+" | awk -F "." '{print $2}' )
        win_rate=$(( 10000-${win_rate} ))   # Inverts the winrate

        blocks[$i]=$( echo "${name};${win_rate}" )

        (( i++ ))
    done

    if [ ${#blocks[@]} -le 10 ]; then   # If there is some data about the matchup, but not enought to give information
        echo "ERROR. There is not enought data for that matchup."
        return 3
    fi


    for ((i=0; i <= $((${#blocks[@]} - 2)); ++i)); do   # Orders array with BubbleSort
        for ((j=((i + 1)); j <= ((${#blocks[@]} - 1)); ++j)); do
            win_rate_i=$( echo "${blocks[i]}" | awk -F ";" '{print $2}' ) # Converts play rates from decimal to numbers between 1000 and 9999
            win_rate_j=$( echo "${blocks[j]}" | awk -F ";" '{print $2}' ) 

            if [[ ${win_rate_i} -lt ${win_rate_j} ]];then
                tmp=${blocks[i]}
                blocks[i]=${blocks[j]}
                blocks[j]=$tmp         
            fi
        done
    done

    echo -e "Counter List vs \e[93m${search_name} \e[96m${search_position}\e[0m: "

    i=1
    for block in ${blocks[@]}; do   # Prints as many counters as user passed
        if [ $i -gt ${max_iterations} ]; then
            break
        fi

        name=$(  echo "${block}" | awk -F ";" '{print $1}' )
        win_rate=$(  echo "${block}" | awk -F ";" '{print $2}' )
        win_rate="${win_rate:0:2}.${win_rate:2}"    # Inserts a point to make winrate decimal again

        echo -e "${i}]\t\e[91m${name}\e[0m(\e[92m${win_rate}%\e[0m)"

        (( i++ ))
    done

}


getClosestChampion(){   # echoes the closest champion according to the given string

    if [  "${#champion_list[@]}" -eq 0 ]; then    # If champion_list is empty find the list
        getChampionList
    fi
    
    #Cleans the name for further matching
    name=$( echo "$1" | tr '[[:upper:]]' '[[:lower:]]' | tr -d '_')


    i=0
    for champ in ${champion_list[@]}; do
        if [[ "${champ}" =~ "${name}" ]]; then
            echo "${champ}"
            return 0
        fi
    done

    return 1
}


getChampionList(){
    champion_list=($( curl -s https://app.mobalytics.gg/champions | egrep -o "/champions/\w+" | awk -F "/" 'BEGIN { ORS=" " }; { print $3} ' ))
}


getUserData(){   
    if [ -z "$2" ]; then
        echo "ERROR. expected user name"
        return 2
    fi

    if [ "$1" = 'a' ]; then   # Specifies if wants info from all champinos
        get_all=1
    else
        get_all=0
    fi

    user_name=$( echo "$2" | sed 's/_/%20/g'  | tr "[[:upper:]]" "[[:lower:]]" )    # Prepares any name to url

    # 1) GENERAL PLAYER DATA
    response=$( curl -s "https://app.mobalytics.gg/profile/euw/${user_name}?queue=RANKED" | ./hxnormalize -x )  # TODO: fix bug where player rol response does not accept accents

    if [ -n "$( echo "${response}" | grep -io "Sorry! We couldn" )" ]; then
        echo "ERROR: Summoner does not exist or isn't aviable for data"
        return 3
    fi
    
    # Obtain user's main role
    role_response=$( echo "${response}" | ./hxselect ".primary-role-overviewstyles__SummonerName-sc-1dpsfor-20\ iYytBo" | ./hxnormalize -x | awk "/<span/&&++k==1,/<\/span/" )
    roles=('top' 'jungle' 'mid' 'adc' 'support')
    main_role="none"
    for role in ${roles[@]}; do
        if [ -n "$( echo "${role_response}" | grep -o "${role}" )" ]; then
            main_role=${role}
            break
        fi
    done

    response=$( curl -s https://euw.op.gg/summoner/userName=${user_name} | ./hxnormalize -x ) # TODO: fix bug where if given a inexistent user_name with accents bugs awk
    
    if [ -n "$( echo "${response}" | ./hxselect ".TierRankInfo" | grep -o "Unranked" )" ]; then # Check if player is unranked
        rank="Unranked"

        total='??'
        win_rate='??'
    else
        rank=$( echo "${response}" | ./hxselect ".TierRankInfo" | ./hxnormalize -x | ./hxselect -c ".TierRank" )

        wins=$( echo "${response}" | ./hxselect ".TierRankInfo" | ./hxnormalize -x | ./hxselect -c ".wins" | tr -dc '[[:digit:]]' )
        losses=$( echo "${response}" | ./hxselect ".TierRankInfo" | ./hxnormalize -x | ./hxselect -c ".losses" | tr -dc '[[:digit:]]' )
        total=$(( wins + losses ))

        win_rate=$( awk "BEGIN {printf \"%.2f\", ${wins}/${total}*100}" )

    fi

    user_data[0]="${user_name};${main_role};${win_rate};${total};${rank}" #Main role; total solo queue winrate; total games played

    # 2) USER'S SPECIFIC DATA FOR EACH CHAMPION
    
    # first we get the summonerId value for that summoner in op.gg so we can get the redirection link
    summoner_id=$( echo "${response}" | ./hxselect ".tabItem\ overview-stats--soloranked" | ./hxnormalize -x | egrep -o "summonerId=[[:digit:]]+" | awk -F "=" '{print $2}' )

    # Now we can get the response to work with
    response=$( curl -s "https://euw.op.gg/summoner/champions/ajax/champions.rank/summonerId=${summoner_id}&season=${SEASON_SEARCH}" | ./hxnormalize -x ) 

    if [ -n "$( echo "${response}" | grep -io "there are no results" )" ]; then
        user_data[1]="none" # Let us know that it couldnt find information about his champions in the current season
        return 1
    fi

    i=2 # Starts at 2 to skip first match
    while true; do  # The champion table is sortered by games played
        match=$( echo "${response}" | awk "/<tr/&&++k==$i,/\/tr>/" )

        if [ ${#match} -lt 2 ];then  # If we have treated all champions, leave loop
            break
        fi

        top_ranker_flag=0
        if [ -n "$( echo "${match}" | grep -o 'Row TopRanker' )" ]; then # Checks if champion is topRanker
            top_ranker_flag=1
        fi

        wins=$( echo "${match}" | egrep -o "[[:digit:]]+W" | tr -dc '[:digit:]' )   
        losses=$( echo "${match}" | egrep -o "[[:digit:]]+L" | tr -dc '[:digit:]' )
        if [ -z "$wins" ]; then # If match was empty, player has 0 Wins/Losses with that champion
            wins=0
        fi
        if [ -z "$losses" ]; then
            losses=0
        fi

        total=$(( wins + losses ))

        if [ ${get_all} -eq 0 ] && [ ${total} -lt ${MIN_GAMES_PLAYED} ] && [ ${top_ranker_flag} -eq 0 ]; then   # skip all champions with less than MIN_GAMES_PLAYED. Ignore topRanker champions.
            break
        fi

        name=$( echo "${match}" | ./hxselect -c ".ChampionName\ Cell" | egrep -o ">([[:alpha:]]+[[:space:]]?)+" | tr -d ">" | tr " " "_" )

        win_rate=$( awk "BEGIN {printf \"%.2f\", ${wins}/${total}*100}" )

        kda=$( echo "${match}" | egrep -o "[[:digit:]]+\.?[[:digit:]]+:1" | awk -F ":" '{print $1}' )
        if [ -z "${kda}" ]; then
            kda="Perfect"
        fi
        

        gold=$( echo "${match}" | awk "/Value Cell/&&++k==1,/</" | egrep -om 1 "[[:digit:]]+," | tr -d "," )

        cs=$( echo "${match}" | awk "/Value Cell/&&++k==2,/</" | egrep -om 1 "[[:digit:]]+\." | tr -d "." )

        damage_dealt=$( echo "${match}" | awk "/Value Cell/&&++k==5,/</" | egrep -om 1 "[[:digit:]]+," | tr -d "," )

        damage_taken=$( echo "${match}" | awk "/Value Cell/&&++k==6,/</" | egrep -om 1 "[[:digit:]]+," | tr -d "," )


        user_data[(( i - 1 ))]="${name};${win_rate};${total};${kda};${gold};${cs};${damage_dealt};${damage_taken}"  # Save each iteration for further use
        (( i++ ))
    done

    return 0
}


printUserData(){
    if [ -z "${user_data[@]}" ]; then
        getUserData $1 $2
    fi

    if [ $? -gt 1 ]; then
        return 1
    fi

    name=${2}

    echo -e "\n---------------------------------------------------------\n"

    # Prints user's data, with a table like style using column tool
    printf "\nUser_Name:;Main_Role:;WinRate:;Games_Played:;Rank:\n" > player_data0.txt
    printf "${name};$( echo "${user_data[0]}" | awk -F ";" '{print $2}' );$( echo "${user_data[0]}" | awk -F ";" '{print $3}' )%%;$( echo "${user_data[0]}" | awk -F ";" '{print $4}' );$( echo "${user_data[0]}" | awk -F ";" '{print $5}' )\n" >> player_data0.txt
    column -s ';' -t player_data0.txt

    if [ "${user_data[1]}" = "none" ]; then
        printf "\nNot enought data for ${name}'s champions in the current season\n\n"
    else
        printf "\n\t\t\tCHAMPIONS:\n"

        # Print user's champion data
        printf "Name:;WinRate:;Games:;KDA:;Gold:;CS:;DMG Dealt:;DMG taken:\n" > player_data0.txt   # We overwrite the file to create the new table
        i=1
        while true; do  # Loops through all the champions and appends it to the file
            if [ -z ${user_data[$i]} ]; then
                break
            fi

            printf "$( echo "${user_data[$i]}" | awk -F ";" '{print $1}' );$( echo "${user_data[$i]}" | awk -F ";" '{print $2}' )%%;$( echo "${user_data[$i]}" | awk -F ";" '{print $3}' );$( echo "${user_data[$i]}" | awk -F ";" '{print $4}' );$( echo "${user_data[$i]}" | awk -F ";" '{print $5}' )K;$( echo "${user_data[$i]}" | awk -F ";" '{print $6}' );$( echo "${user_data[$i]}" | awk -F ";" '{print $7}' )K;$( echo "${user_data[$i]}" | awk -F ";" '{print $8}' )K\n" >> player_data0.txt

            (( i++ ))
        done
        column -s ';' -t player_data0.txt   # Prints a table with the file created in the last loop

        echo -e "\n---------------------------------------------------------\n"
    fi

    rm player_data0.txt

    return 0
}

getMatchUp(){
    user_name=$( echo "$1" | sed 's/_/%20/g'  | tr "[[:upper:]]" "[[:lower:]]" )    # Prepares any name to url
    
    response=$( curl -s "https://euw.op.gg/summoner/spectator/userName=${user_name}" | ./hxnormalize -x )

    # Checks if user name exists
    if [ -z "${response}" ]; then   
        echo "ERROR: Summoner does not exist or isn't aviable for data"
        return 1
    
    elif [ -n "$( echo "${response}" | grep -io "is not in an active game" )" ]; then    # Checks if user is in game
        echo "ERROR: summoner is not in an active game. Try again later"
        return 2
    fi

    echo -e "\n---------------------------------------------------------"

    for (( i=1; i<=2; i++ )); do    # Loops through blue and red team, respectively

        case $i in
            1) 
                printf "\n\e[94mBlue Team:\e[0m\n\n"
            ;;
            2) 
                printf "\n\e[91mRed Team:\e[0m\n\n"
            ;;
        esac
        

        # Use column just like 'printUserData'
        printf "User_Name:;WinRate:; Rank:;Games_Played:;Champion_Name:;Champion_WinRate:;Champion_Games_Played:;Champion_KDA:\n\n" > player_data0.txt

        blue_table=$( echo "${response}" | ./hxselect -c ".Table\ Team-${i}00" | ./hxnormalize -x )
        for (( j=1; j<=5; j++ )); do  # Each iteration cuts with sed the portion we need for each role

            row=$( echo "${blue_table}" | awk "/SpectateBig/&&++k==${j},/<\/tr>/" )

            champion_name=$( echo "${row}" | egrep -o "/champion/[[:alpha:]]+/statistics" | awk -F "/" '{print $3}' )

            user_name=$( echo "${row}" | egrep -io "/summoner/userName=[^[:space:]]+" | awk -F "=" '{print $2}' | tr -d '"' )
            # Fixes special characters
            user_name=$( echo "$user_name" | sed 's/%.*%/?/' )  # TODO: fix and print special characters

            rank=$( echo "${row}" | ./hxselect -c ".TierRank" | ./hxnormalize -x )
            # Checks if the player has rank yet
            if [ -n "$( echo "${rank}" | grep -io "level" )" ]; then
                rank=" UnRanked"
            else
                rank=$( echo "${rank}" | ./hxselect -c p )
            fi

            user_game_data=$( echo "${row}" | ./hxselect -c ".RankedWinRatio" | ./hxnormalize -x )
            
            user_winrate=$( echo "${user_game_data}" | ./hxselect -c ".Ratio" )
            # If there isnt enought data about players winrate
            if [ -z "${user_winrate}" ]; then   
                user_winrate="-%"
            fi

            user_games_played=$( echo "${user_game_data}" | ./hxselect -c ".TotalCount" )
            # If there isnt enought data about player's games with the champion
            if [ -z "${user_games_played}" ]; then   
                user_games_played=""
            fi

            champion_winrate=$( echo "${row}" | ./hxselect -c ".ChampionInfo" | ./hxnormalize -x | ./hxselect -c ".Ratio" )

            champion_games_played=$( echo "${row}" | ./hxselect -c ".ChampionInfo" | ./hxnormalize -x | egrep -io "[[:digit:]]+ Played" )
            # If there isnt enought data about player's games winrate with the champion
            if [ -z "${champion_winrate}" ]; then   
                champion_winrate="-%"
                champion_games_played="-"
            fi

            champion_kda=$( echo "${row}" | ./hxselect -c ".ChampionInfo" | ./hxnormalize -x | ./hxselect -c "span.KDA" )
            if [ -z "${champion_kda}" ]; then   # If there isnt enought data about players kda with the champion
                champion_kda="-"
            fi

            # Appends each iteration to the file
            printf "${user_name};${user_winrate}%;${rank};${user_games_played};${champion_name};${champion_winrate}%;${champion_games_played};${champion_kda}\n" >> player_data0.txt

        done
        column -s ';' -t player_data0.txt
    done

    echo -e "\n---------------------------------------------------------\n"


    rm player_data0.txt

    return 0
}


printHelp(){
    echo -e "\nlolboost: League of Legends statistics and more!\n"

    echo -e "Usage: lolboost [OPTION]\n"

    echo -e "-h,--help :\n\tPrint help\n"

    echo -e "-t,--tier :\n\tDisplays champion tier list in the current meta for every role\n"

    echo -e "-w,--win champion_name position :\n\tShows champion's actual winrate on given position\n"

    echo -e "-c,--count [-n] [list_count] champion_name position :\n\tLists different counterpicks against a champion on the given position\n\t-n list_count to choose the number of champions listed\n"

    echo -e "-s,--stat [-a] user_name :\n\tDisplays information about the user and it's main champions\n\t-a flag to list all user's champions played on the current season\n"

    echo -e "-m,--match user_name :\n\tDisplays data about user's live game. The given user must be in a match\n"

    echo -e "\nRemember to use '_' instead of whitespaces since we are using bash\nAvoid using special characters such as ' on champion names\n"

}


# Program Starts Here

declare -a champion_list
declare -a user_data

# Checks internet connectivity
check=$( curl -s "https://euw.op.gg/" )

if [ ${?} -ne 0 ]; then
    echo "ERROR: please check that you have access to internet"
    exit 2

fi


# Works the flags and arguments
case $1 in
    '-h'|'--help' ) 
        printHelp
    ;;
    '-w'|'--win'* ) 
        if [ -z "$2" ] || [ -z "$3" ]; then
            echo "ERROR: expected 2 arguments: -w champion_name position"
            exit 1
        fi
        searchWinrate $2 $3 'v'
    ;;
    '-t'|'--tier'* ) 
        getTierList
    ;;
    '-c'|'--count'* ) 
        if [ -z "$2" ] || [ -z "$3" ]; then
            echo "ERROR: expected at least 2 arguments: -c [-n] [list_count] champion_name position"
            exit 1
        fi
        getCounterList $2 $3 $4 $5
    ;;
    '-s'|'--stat'* ) 
        if [ -z "$2" ]; then
            echo "ERROR: expected user_name: -s [-a] user_name"
        elif [[ $2 =~ "-" ]]; then
            if [ $2 = '-a' ] || [ $2 = '--all' ]; then
                printUserData 'a' $3
            else
                echo "Invalid argument '${2}'"
            fi
        else
            printUserData 'n' $2
        fi

    ;;
    '-m'|'--match'* ) 
        if [ ${#@} -ne 2 ]; then
            echo "ERROR: expected only an user_name: -m user_name"
            exit 1
        fi
        getMatchUp $2
    ;;
    '')
        echo "Argument expected. type -h or --help for help"
        exit 1
    ;;
    *)
        echo "Invalid argument '${1}'"
        exit 1
    ;;
esac

exit 0

