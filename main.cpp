#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <fstream>
//#include "Graph.h"
#include "board.h"

using namespace std;
struct command
{
  char robot;
  unsigned short dir;
}typedef command;
command last;

bool
findPath(const Board &c, vector<command> &path, int depth)
{
  Board temp = c;
  if (c.getGoalRobot() == -1)
    for (int i = 0; i < c.numRobots(); i++)
      {
        if (c.getRobotPosition(i) == c.getGoal())
          {
//            temp.print();
            return true;
          }
      }
  else if (c.getRobotPosition(c.getGoalRobot()) == c.getGoal())
    return true;
  if (depth != 0)
    {

      for (unsigned int i = 0; i < c.numRobots(); i++)
        {
          for (unsigned short d = 0; d < 4; d++)
            {
              temp = c;
              command tq;

              tq.dir = d;
              tq.robot = c.getRobot(i);
              if (temp.moveRobot(i, d))
                if (findPath(temp, path, depth - 1))
                  {
//                    temp.print();
                    path.push_back(tq);
                    return true;
                  }

            }

        }
    }
  return false;
}

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

// ================================================================
// ================================================================

int
main(int argc, char* argv[])
{
//  white::Node g;
//  g.Robots.push_back(Position(22, 133));
//  g.Robots.push_back(Position(24, 122));
//  g.edges.push_back(new white::Node());
//  std::cout << std::hex << g.hash() << std::endl;
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

  // for now...  an example of how to use the board print function
  vector<command> d;
  board.print();
  findPath(board, d, 12);

  for (int i = d.size(); i >= 0; i--)
    {
      std::cout << d[i].robot << ":";
      switch (d[i].dir)
        {
      case 0:
        std::cout << "North";
        break;
      case 1:
        std::cout << "East";
        break;
      case 2:
        std::cout << "South";
        break;
      case 3:
        std::cout << "West";
        break;
        }
      std::cout << std::endl;
    }

}

// ================================================================
// ================================================================
