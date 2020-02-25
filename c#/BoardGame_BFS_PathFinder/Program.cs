// A PathFinder used in a board game based on BFS which returns both the path (in nodes) to follow and the distance

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PathFinder
{
    class Program
    {
        static void Main(string[] args)
        {
            int[,] matrix = { { 0, 0, 0, 0, 0, 0},
                              { 0, 1, 0, 1, 1, 0},
                              { 0, 0, 0, 1, 0, 1},
                              { 1, 0, 0, 1, 1, 0},
                              { 0, 0, 0, 0, 0, 0}};
            Position start = new Position(2,0);
            Position destination = new Position(1, 5);

            PathFinder pathFinder = new PathFinder();
            List<Position> shortest_path = pathFinder.FindPath(matrix, start, destination, 1);
            int path_distance;

            if (shortest_path != null)
            {
                for (int i = shortest_path.Count -1; i >= 0; i--) {
                    var item = shortest_path[i];
                    string pr = "(" + item.X.ToString() + "," + item.Y.ToString() + ")";
                    Console.WriteLine(pr);
                }
                path_distance = shortest_path.Count();
                Console.WriteLine("Distance: " + path_distance.ToString());
            }
            else
            {
                Console.WriteLine("There is no solution");
            }

        }
    }

    public struct Position
    {
        private int x;
        public int X { 
            get { 
                return x; } 
            set {
                x = value;
            } }

        private int y;
        public int Y
        {
            get
            {
                return y;
            }
            set
            {
                y = value;
            }
        }

        public Position(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }

    public class PathFinder
    {
        //used by the queue of BFS
        private class QItem
        {
            public Position position;
            public int distance;
            public QItem last_item;
            
            public QItem(int _x, int _y, int _distance, QItem _last_item)
            {
                this.position.X = _x;
                this.position.Y = _y;
                this.distance = _distance;
                this.last_item = _last_item;
            }
        };


        // Returns a list of Qitems with the positions of each node of the shortest path
        public List<Position> FindPath(int[,] _matrix, Position _start, Position _destination, int _flight_value) //flight_value is used if we want entities to fly, be ghosts...
        {
            Queue<QItem> queue = new Queue<QItem>();
            int n_rows = _matrix.GetLength(0);
            int n_columns = _matrix.GetLength(1);
            bool[,] visited = new bool[n_rows, n_columns];


            // Initialize working grid
            for (int i = 0; i < n_rows; i++)
            {
                for (int j = 0; j < n_columns; j++)
                {
                    if(_flight_value <= _matrix[i, j])
                    {
                        visited[i, j] = true;
                    }
                    else
                    {
                        visited[i, j] = false;
                    }
                }
            }

            // Check for an invalid destination
            if (!IsValidPosition(_destination, n_rows, n_columns, visited))
            {
                return null;
            }

            Position[] directions = new Position[4];
            // Left
            directions[0] = new Position(0, -1);
            // Up
            directions[1] = new Position(1, 0);
            // Right
            directions[2] = new Position(0, 1);
            // Down
            directions[3] = new Position(-1, 0);

            // Start the search
            queue.Enqueue(new QItem(_start.X, _start.Y, 0, null));
            visited[_start.X, _start.Y] = true;
            Position temp_pos = new Position(-1, -1);  // Used to loop through multiple positions

            while(queue.Count() > 0)
            {
                QItem p = queue.Dequeue();

                // We found the path to exit
                if (p.position.X == _destination.X && p.position.Y == _destination.Y)
                {
                    // Create the array for the path
                    List<Position> shortest_path = new List<Position>();
                    QItem temp_qitem = p;

                    while(temp_qitem.last_item != null)
                    {
                        shortest_path.Add(temp_qitem.position);
                        temp_qitem = temp_qitem.last_item;
                    }

                    return shortest_path;
                }

                // Try for next cell in all directions:
                for (int k = 0; k < 4; k++)
                {
                    temp_pos.X = p.position.X + directions[k].X;
                    temp_pos.Y = p.position.Y + directions[k].Y;
                    if (IsValidPosition(temp_pos, n_rows, n_columns, visited))
                    {
                        queue.Enqueue(new QItem(temp_pos.X, temp_pos.Y, p.distance + 1, p));
                        visited[temp_pos.X,temp_pos.Y] = true;
                    }
                }
            }

            return null;

        }

        private bool IsValidPosition(Position _p, int _n_rows, int _n_columns, bool[,] visited)
        {
            if (_p.X < 0 || _p.Y < 0 ||
                _p.X >= _n_rows || _p.Y >= _n_columns ||
                visited[_p.X, _p.Y])
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}
