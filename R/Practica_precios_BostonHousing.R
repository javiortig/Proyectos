#-----apuntes mios: primero hacer la practica y luego si quiero mejorarla

# PRACTICA 1. PROBABILIDAD Y ESTADÍSTICA.
# En la siguiente práctica se pide:
# 1. Instalar e importar la librería mlbench y cargar los datos "BostonHousing" 

install.packages("mlbench")
library(mlbench)

data("BostonHousing")
housing <- BostonHousing

# CRIM: Per capita crime rate by town
# ZN: Proportion of residential land zoned for lots over 25,000 sq. ft
# INDUS: Proportion of non-retail business acres per town
# CHAS: Charles River dummy variable (= 1 if tract bounds river; 0 otherwise)
# NOX: Nitric oxide concentration (parts per 10 million)
# RM: Average number of rooms per dwelling
# AGE: Proportion of owner-occupied units built prior to 1940
# DIS: Weighted distances to five Boston employment centers
# RAD: Index of accessibility to radial highways
# TAX: Full-value property tax rate per $10,000
# PTRATIO: Pupil-teacher ratio by town
# B: 1000(Bk - 0.63)², where Bk is the proportion of [people of African American descent] by town
# LSTAT: Percentage of lower status of the population
# MEDV: Median value of owner-occupied homes in $1000s

# 1) Inspeccionar los datos con el comando str(), head(), dim(), summary()
# Describir las 5 características de los datos que os parezcan más importantes

str(housing)  #Muestra todos los datos divididos en sus valores por cada variable
head(housing) #Muestra los primeros datos
dim(housing)  #Muestra el num de observaciones y su num de variables
summary(housing) #Muy util. Muestra un resumen de varios estadísticos relevantes para cada
                 #variable. Estos se corresponden con los que nos daría un boxplot

#Las 5 variables más importantes que nos pueden ayudar a medir el MEDV de una vivienda 
#podrían ser:
#1) TAX: ya que se trata de el impuesto aplicado sobre el valor de la vivienda
#2) RM: nos dice el numero de habitaciones por vivienda, y por lo tanto, nos sirve como un
#indicador importante a la hora de determinar el tamaño y capacidad de la vivienda.
#3) LSTAT: % de poblacion que pertenece a una clase baja, por lo que se trata de un medidor
#inversamente proporcional a la variable dependiente MEDV
#4) PTRATIO: nos indica la proporción entre profesores-alumnos, es decir, el nº de alumnos
#que tiene cada profesor. Este valor puede sernos de gran utilidad ya que los colegios de
#clase alta suelen tener clases con menor número de alumnos respecto a los demás. Por lo tanto,
#esperamos que este valor nos sirva como un predictor inversamente proporcional.
#5) AGE: que nos dice la proporcion de casas construidas antes de 1940. Es muy util ya que
#la antiguedad de una vivienda y de una zona influye mucho en su valor. Además de que las zonas
#con abundantes viviendas antiguas suelen ser las más céntricas

#Esto es lo que nos dice la intuición, pero no podremos afirmar nada hasta realizar el estudio
#estadístico que le corresponde a los datos

# Nuestra variable de interés es MEDV, que muestra el valor medio de las viviendas
# Este valor medio creemos que se puede predecir en función del resto de variables
# Antes de realizar un análisis de regresión lineal, realizaremos un análisis exploratorio
# 2) Explorar y visualizar la distribución de la variable dependiente
# Para ello, utilizad los comandos hist, summary. La calidad de las imágenes y las descripciones, puntuan.

hist(housing$medv, xlab = "Valor medio de las viviendas en $1000s",
     ylab = "Frecuencia", col="darkmagenta", breaks = 10)
#Es importante el valor 'break' en un histograma, ya que puede cambiar por completo la
#interpretacion y la distribucion del histograma. Por tanto:
hist(housing$medv, xlab = "Valor medio de las viviendas en $1000s",
     ylab = "Frecuencia", col="darkgreen", breaks = 20)
hist(housing$medv, xlab = "Valor medio de las viviendas en $1000s",
     ylab = "Frecuencia", col="darkblue", breaks = 40)

#En este caso coger valores distintos para 'break' no varía mucho la distribucion de las
#frecuencias ni la interpretacion que podemos sacar del histograma

summary(housing$medv)
#Con summary y hist ya podemos saber ciertos datos relevantes sobre MEDV:
#Presenta una asimetría positiva, la mitad de los datos están concentrados entre 
#Q1=17.02 y Q3=25 por lo que teniendo un IQR=7,98 y siendo el min 5 y el max 50 sabemos que
#la gráfica es leptocúrtica ya que la mayoría de datos se acumulan en ese pequeño rango.
#Aunque la mediana se encuentre en 21.20 por el histograma con break=20 vemos que gran 
#parte de los valores de las viviendas entran en el intervalo [18,24].




# 3) Explorar la correlacion de pearson entre variables. Cread la matriz de correlacion. 
# Utilizad el comando corrplot de la libreria "corrplot" para mejorar la experiencia visual.
# La descripción de las correlaciones puntuan

install.packages("corrplot")
library(corrplot)

#Primero debemos convertir a numeric la variable chas para poderla pasar por la funcion cor()
#ya que solo acepta valores numericos y hemos recibido chas como un factor de dos niveles (0,1)
#en la conversion los valores de chas pasan a ser 1,2 respectivamente
str(housing)
housing$chas = as.integer(housing$chas)

#creamos la matriz de correlacion
m_cor = cor(housing)

#Utilizamos corrplot como herramienta para visualizar la matriz de correlación:
corrplot(m_cor, method = "circle", title = "Matriz de correlacion BostonHousing", type = "lower")

#Utilizamos valores numéricos de corrplot para elegir adecuadamente nuestros predictores
corrplot(m_cor, method = "number", title = "Matriz de correlacion BostonHousing", type = "lower")

#Apreciaciones: obviamente la diagonal principal de la matriz tiene valores 1 ya que se
#trata de la correlacion de cada variable consigo misma. Vemos que algunas variables como
#'dis' tiene una fuerte relacion inversa con 'indus', 'nox' y 'age'. Pero a nosotros nos
#interesa nuestra variable dependiente 'medv', por tanto:
#El valor de la vivienda se ve directamente afectado claramente por el numero
#de habitaciones('rm'). Además tiene una gran relacioón inversa con el % de población de 
#clase baja ('lstat'). Con esta matriz también podemos observar variables que afectan de
#manera insignificante o en nada al precio de la vivienda, como pueden ser 'chas' y 'dis'



# 4) Escoger los 4 mejores predictores y realizar tres regresiones simples con ellos.
# Explorar los resultados mediante scatterplots y las rectas dibujadas
# La descripción de las graficas y modelos asi como la calidad de las gráficas, puntuan

  #1 lstat,2 rm, 3 ptratio, 4 indus

  linearModel = NULL
  
  linearModel$lstat = lm(formula = housing$medv~ housing$lstat )
  plot(x = housing$lstat, y =housing$medv, 
       main="Regresión lineal con lstat",xlab = "% poblacion de clase baja",
       ylab = "Valor de las viviendas (en $1000s)")
  abline(linearModel$lstat, col="red")
  
  
  linearModel$rm = lm(formula = housing$medv~ housing$rm )
  plot(x = housing$rm, y =housing$medv, 
       main="Regresión lineal con rm",xlab = "valor medio de habitaciones",
       ylab = "Valor de las viviendas (en $1000s)")
  abline(linearModel$rm, col="red")

  linearModel$ptratio = lm(formula = housing$medv~ housing$ptratio )
  plot(x = housing$ptratio, y =housing$medv, 
       main="Regresión lineal con ptratio",xlab = "relacion nº de alumnos por profesor",
       ylab = "Valor de las viviendas (en $1000s)")
  abline(linearModel$ptratio, col="red")
  
#-Lstat: tal y como esperábamos, la regresión tiene una pendiente negativa(inversamente
#proporcional). En general, los valores siguen el patrón de la recta. Se puede apreciar
#valores que deberían ser limpiados al considerarse outliers.
#-rm: la mayoría de valores se ajustan bastante bien para 5<x<7, sin embargo, se parecia
#claramente outliers al igual que en la gráfica anterior. Evidentemente, la recta tiene una
#pendiente positiva ya que como nos dice nuestro sentido común, el nº de habitaciones de una
#vivenda nos dice cómo de grande es, y el tamaño influye mucho en su precio
#-ptratio: vemos que la recta no se ajusta adecuadamente a los datos, que en muchos casos se
#alejan mucho de su predicción. Sin embargo, si vemos que tiene sentido que la recta tenga
#una pendiente negativa, ya que como comentamos anteriormente, a menor nº alumnos por profesor,
#mayor calidad suele tener el colegio(con excepciones obvias como puede ser un pueblo pequeño
#o una zona con riesgo de  despoblación)
  
  
# 5) Mostrar en un scatterplot los residuos y las variables ajustadas de cada modelo.
# Para ello, será necesario realizar una predicción de los valores mdev
# La descripción de las graficas e interpretación, puntua
res = NULL
  
#Calculamos los residuos de cada regresión
  
res$lstat = resid(linearModel$lstat)
res$rm = resid(linearModel$rm)
res$ptratio = resid(linearModel$ptratio)  

#Predecimos los valores para cada modelo

prediction = NULL

prediction$lstat = predict(linearModel$lstat)
prediction$rm = predict(linearModel$rm)
prediction$ptratio = predict(linearModel$ptratio)
  
#Dibujamos las gráficas de cada linearModel
plot(x = prediction$lstat, y = res$lstat, 
     xlab = "Valores ajustados de lstat",
     ylab = "Residuos", main = "Residuos vs Valores ajustados de lstat")
abline(0,0, col = "blue")

plot(x = prediction$rm, y = res$rm, 
     xlab = "Valores ajustados de rm",
     ylab = "Residuos", main = "Residuos vs Valores ajustados  de rm")
abline(0,0, col = "blue")

plot(x = prediction$ptratio, y = res$ptratio, 
     xlab = "Valores ajustados de ptratio",
     ylab = "Residuos", main = "Residuos vs Valores ajustados de ptratio")
abline(0,0, col = "blue")

#Vemos que en el caso de lstat los residuos están mayoritariamente por debajo
#de y=0. En el caso de rm, la mayoría de residuos se encuentran concentrados
#en y=0, por lo que nos indica que la recta de regresión ha sido bastante 
#acertada. Por último, y como era de esperar, ptratio muestra el peor de los
#resultados(tal y como esperabamos tras ver la matriz de correlación), ya
#que los residuos tienen valores poco uniformes.

#Utilizamos la función plot() y nos fijamos en la primera gráfica que nos 
#muestra (pulsar return 1 vez en la consola):
plot(linearModel$lstat)

plot(linearModel$rm)

plot(linearModel$ptratio)

#Para el caso de lstat vemos que el scatterplot de los residuos forma
#un patrón no-lineal, por lo que habría que plantearse utilizar una regresión
#polinómica de grado >=2.
#Sin embargo, en los casos de rm y ptratio no podemos sospechar en principio
#de que el scatterplot siga un patrón no-lineal.


# 6) Realizar una regresión lineal múltiple con los 4 predictores. 
# Y mostrar en un scatterplot los residuos y las variables ajustadas de este modelo.
# La descripción de las graficas y modelos asi como la calidad de las gráficas, puntuan

#Realizamos la regresión lineal múltiple
linearModel$all = lm(housing$medv ~ housing$lstat + housing$rm +
              housing$ptratio + housing$indus )

#Seguimos los pasos exactamente igual que en el ejercicio anterior

res$all = resid(linearModel$all)

prediction$all = predict(linearModel$all)

plot(x = prediction$all, y = res$all, xlab = "Valores ajustados",
     ylab = "Residuos", main = "Residuos vs valores ajustados")
abline(0,0,col = "blue")

#Podemos observar que, aunque haya muchos residuos esparcidos(esto se 
#debe a no eliminar los outliers antes de realizar el modelo) la mayoría
#se concentran sobre y=0, tal y como esperábamos.

#Utilizamos la función plot() y nos fijamos en la primera gráfica que nos 
#muestra (pulsar return 1 vez en la consola):

plot(linearModel$all)

#Vemos que en el caso de la regresión múltiple, el scatterplot nos muestra
#un patrón no lineal, por lo que quizás podríamos plantearnos, al igual que hemos
#mencionado en el ejercicio anterior, utilizar un modelo no lineal


#Conclusiones: en esta práctica hemos podido aprender que es necesario realizar ciertos pasos
#previos para construir un moledo de predicción adecuado. Algunos nos hemos ejecutado 
#correctamente, como analizar de forma intuitiva los datos, construir la matriz de correlación
#para elegir adecuadamente cuales van a ser nuestros predictores y estudiar la frecuencia de
#nuestra variable dependiente con el histograma usando varios 'breaks'.
#Sin embargo, hay otros pasos muy importantes que no hemos ejecutado, como puede ser:
#limpiar nuestros datos de outliers, algo imprescindible, ya que estos afectarán mucho a la hora
#de crear la regresión y limpiarlos supondría obtener un modelo más fiable y en consecuencia
#un scatterplot de residual vs fitted values más razonable.

#Tampoco nos hemos fijado en otras herramientas esenciales que nos ofrece la estadística como
#podemos observar por ejemplo con el comando summary():

summary(linearModel$all)

#Si nos fijamos en los coeficientes, y en concreto en la columna 'Pr(>|t|)'. Esta columna nos da
#una información muy valiosa, ya que podemos ver la calidad de cada una de nuestras variables
#independientes a la hora de aportar valor en el modelo. En nuestro caso se ve claramente que
#las tres primeras variables son muy útiles y que sin embargo la variable 'indus' no nos aporta
#nada y por lo tanto deberíamos descartarla. 
#Otro valor imprescindible es el p-value(que también nos muestra este comando), 
#que nos permite descartar la hipótesis nula(la hipótesis nula es una suposición
#que se utiliza para negar o afirmar la relación entre las variables
# independientes y la dependiente).
#Por convenio, normalmente para el p-value se coge un valor alfa=0.05, y como en nuestro
#caso hemos obtenido que nuestro p-value<2.2*10^-16<alfa -> afirmamos que nuestras variables 
#escogidas tienen una gran correspondencia con medv y por lo tanto podemos rechazar la 
#hipótesis nula.