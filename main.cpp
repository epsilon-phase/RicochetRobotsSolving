#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <fstream>
//#include "Graph.h"
#include "board.h"
#include <limits>
using namespace std;

#include "command.h"
//TODO fix so that unconstrained max depth does not cause program to attempt to create an infinite path to the goal.

//silly algorithm. Fails to find shortest path answer consistently.
bool
findPath(const Board &c, std::vector<command> &path, int depth,
    const command &last = command())
{
  //due to the algorithm's incorrect handling of infinite allowable depth,
  //I see no reason not to make a ridiculously high limit.
  if (depth == -1)
    depth = c.getCols() * c.getRows();
  Board temp = c;
  if (c.getGoalRobot() == -1)
    for (unsigned int i = 0; i < c.numRobots(); i++)
      {
        if (c.getRobotPosition(i) == c.getGoal())
          {
//            temp.print();
            return true;
          }
      }
  else if (c.getRobotPosition(c.getGoalRobot()) == c.getGoal())
    return true;
  if (depth > 0)
    {

      for (unsigned int i = 0; i < c.numRobots(); i++)
        {
          for (unsigned short d = 0; d < 4; d++)
            {
              temp = c;
              //If the robot moves in one direction, it will never
              //be able to move in the same direction twice consequently.
              if (last.dir != d || last.robonum != i)
                if (temp.moveRobot(i, d))
                  if (findPath(temp, path, depth - 1,
                      command(temp.getRobot(i), i, d)))
                    {
//                    temp.print();
                      path.push_back(command(c.getRobot(i), d));

                      return true;
                    }

            }

        }
    }
  return false;
}

void
getAccessibility(const Board& f, vector<vector<int> > &h, unsigned int maxdepth,
    unsigned int curdepth = 0);
// ================================================================
// ================================================================
// This function is called if there was an error with the command line arguments
bool
usage(const std::string &executable_name)
{
  std::cerr << "Usage: " << executable_name << " <puzzle_file>" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#>"
      << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -all_solutions"
      << std::endl;
  std::cerr << "       " << executable_name
      << " <puzzle_file> -visualize_accessibility" << std::endl;
  std::cerr << "       " << executable_name
      << " <puzzle_file> -max_moves <#> -all_solutions" << std::endl;
  std::cerr << "       " << executable_name
      << " <puzzle_file> -max_moves <#> -visualize_accessibility" << std::endl;
  exit(0);
}

// ================================================================
// ================================================================
// load a Ricochet Robots puzzle from the input file
Board
load(const std::string &executable, const std::string &filename)
{

  // open the file for reading
  std::ifstream istr(filename.c_str());
  if (!istr)
    {
      std::cerr << "ERROR: could not open " << filename << " for reading"
          << std::endl;
      usage(executable);
    }

  // read in the board dimensions and create an empty board
  // (all outer edges are automatically set to be walls
  int rows, cols;
  istr >> rows >> cols;
  Board answer(rows, cols);

  // read in the other characteristics of the puzzle board
  std::string token;
  while (istr >> token)
    {
      if (token == "robot")
        {
          char a;
          int r, c;
          istr >> a >> r >> c;
          answer.placeRobot(Position(r, c), a);
        }
      else if (token == "vertical_wall")
        {
          int i;
          double j;
          istr >> i >> j;
          answer.addVerticalWall(i, j);
        }
      else if (token == "horizontal_wall")
        {
          double i;
          int j;
          istr >> i >> j;
          answer.addHorizontalWall(i, j);
        }
      else if (token == "goal")
        {
          std::string which_robot;
          int r, c;
          istr >> which_robot >> r >> c;
          answer.setGoal(which_robot, Position(r, c));
        }
      else
        {
          std::cerr << "ERROR: unknown token in the input file " << token
              << std::endl;
          exit(0);
        }
    }

  // return the initialized board
  return answer;
}
void
printAccessibility(const vector<vector<int> > &y);

// ================================================================
// ================================================================

int
main(int argc, char* argv[])
{

  // There must be at least one command line argument, the input puzzle file
  if (argc < 2)
    {
      usage(argv[0]);
    }

  // By default, the maximum number of moves is unlimited
  int max_moves = -1;

  // By default, output one solution using the minimum number of moves
  bool all_solutions = false;

  // By default, do not visualize the accessibility
  bool visualize_accessibility = false;

//  // Read in the other command line arguments
  for (int arg = 2; arg < argc; arg++)
    {
      if (argv[arg] == std::string("-all_solutions"))
        {
          // find all solutions to the puzzle that use the fewest number of moves
          all_solutions = true;
        }
      else if (argv[arg] == std::string("-max_moves"))
        {
          // the next command line arg is an integer, a cap on the  # of moves
          arg++;
          assert(arg < argc);
          max_moves = atoi(argv[arg]);
          assert(max_moves > 0);
        }
      else if (argv[arg] == std::string("-visualize_accessibility"))
        {
          // As a first step towards solving the whole problem, with this
          // option, let's visualize where the robots can move and how many
          // steps it takes to get there
          visualize_accessibility = true;
        }
      else
        {
          std::cout << "unknown command line argument" << argv[arg]
              << std::endl;
          usage(argv[0]);
        }
    }

  // Load the puzzle board from the input file
  Board board = load(argv[0], argv[1]);

  //
  //
  // YOUR CODE STARTS HERE
  //
  //

  if (!visualize_accessibility)
    {
      // for now...  an example of how to use the board print function
      vector<struct command> d;
      board.print();
      int mx;
      //Try finding a shorter solution than specified, if only because the algorithm still lacks proper handling for the correct behavior.
      for (mx = max_moves - 2; d.empty() && mx <= max_moves; mx++)
        {
          findPath(board, d, mx);
        }
      if (!d.empty())
        {
          for (int i = d.size() - 1; i >= 0; i--)
            {

              std::cout << "Robot " << d[i].robot << " moves ";
              switch (d[i].dir)
                {
              case 0:
                std::cout << "north";
                break;
              case 1:
                std::cout << "east";
                break;
              case 2:
                std::cout << "south";
                break;
              case 3:
                std::cout << "west";
                break;
                }
              cout << endl;
              if (!all_solutions)
                {
                  board.executeCommand(d[i]);

                  board.print();
                }
            }
          cout << "robot " << d.back().robot << " reaches the goal after "
              << mx - 1 << " moves" << endl;
        }
      else
        {
          cout << "no solutions with " << max_moves << " or fewer moves"
              << endl;
        }
    }
  else
    {
      vector<vector<int> > itz;
      getAccessibility(board, itz, max_moves, 0);
      printAccessibility(itz);
    }

}
void
getAccessibility(const Board& f, vector<vector<int> > &h, unsigned int maxdepth,
    unsigned int curdepth)
{
  //Initialize the vector to the correct size
  if (curdepth == 0)
    {
      h.resize(f.getRows());
      for (unsigned int c = 0; c < f.getRows(); c++)
        {
          h[c] = vector<int>(f.getCols(), std::numeric_limits<int>::max());
          //using a reference should reduce the number of calls to operator[] by about 2*n
          vector<int> &reffy = h[c];
          //initialize inner vector
          for (unsigned int g = 0; g < h[c].size(); g++)
            reffy[g] = std::numeric_limits<int>::max();
        }
    }
  if (curdepth <= maxdepth)
    {

      for (unsigned int g = 0; g < f.numRobots(); g++)
        {

          for (unsigned short c = 0; c < 4; c++)
            {  //copy to a temporary variable
               //needs to happen in order to explore the movement spaces of the robots properly
              Board temp = f;
              Position curbot = temp.getRobotPosition(g);
              if (h[curbot.row - 1][curbot.col - 1] > curdepth)
                h[curbot.row - 1][curbot.col - 1] = curdepth;
              if (temp.moveRobot(g, c))
                {

                  getAccessibility(temp, h, maxdepth, curdepth + 1);
                  //if the position is found with a smaller number of turns, then this is nice.

                }
            }
        }
    }
  else
    {

      for (vector<vector<int> >::iterator r = h.begin(); r != h.end(); r++)
        {
          for (vector<int>::iterator g = r->begin(); g != r->end(); g++)
            if (*g == numeric_limits<int>::max())
              *g = -1;
        }
    }

}
void
printAccessibility(const vector<vector<int> > &y)
{
  for (unsigned int c = 0; c < y.size(); c++)
    {
      for (unsigned int d = 0; d < y[c].size(); d++)
        {

          cout.width(4);
          if (y[c][d] >= 0)
            cout << y[c][d] << " ";
          else
            cout << '.' << " ";
        }
      cout << endl;
    }
}
// ================================================================
// ================================================================
