#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>   // for colors
#include<chrono>
#include<thread>
#include <iostream>
#include <vector>
using namespace ftxui;


void highlight_path(const std:: vector<std::string>&grid, const std::vector<std::pair<int,int>>&path){
    int rows = grid.size(), cols = grid[0].length();
    auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
    std::vector<std::vector<Color>> grid_colors(rows, std::vector<Color>(cols, Color::GrayLight));
    auto render_grid = [&]() {
        std::vector<std::vector<Element>> matrix;
        for (int r = 0; r < rows; r++) {
            std::vector<Element> row;
            for (int c = 0; c < cols; c++) {
                row.push_back(
                    text(std::string(1, grid[r][c])) | bgcolor(grid_colors[r][c]) | border
                );
            }
            matrix.push_back(row);
        }
        return gridbox(matrix);
    };

    for (auto [r, c] : path) {
        grid_colors[r][c] = Color::Green;

        // Clear + render updated grid
        screen.Clear();
        Render(screen, render_grid());
        screen.Print();

        // Delay for animation
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    // screen.Print(render_grid());
    std::this_thread::sleep_for(std::chrono::seconds(3));

}

void show_grid(const std::vector<std::string>&grid){
    int rows = grid.size(), cols = grid[0].length();

  // Fill grid with characters (example: A, B, C...)
//   std::vector<std::vector<char>> grid(rows, std::vector<char>(cols, ' '));
//   char ch = 'A';
//   for (int r = 0; r < rows; r++) {
//     for (int c = 0; c < cols; c++) {
//       grid[r][c] = ch;
//       ch = (ch == 'Z' ? 'A' : ch + 1); // loop A-Z
//     }
//   }

  // Convert grid into FTXUI elements
  std::vector<Element> rows_elements;
  for (int r = 0; r < rows; r++) {
    std::vector<Element> row;
    for (int c = 0; c < cols; c++) {
      row.push_back(text(std::string(1, grid[r][c])) | border);
    }
    rows_elements.push_back(hbox(row));
  }

  // Combine all rows into a bordered grid
  auto doc = vbox(rows_elements) ;

  // Render on screen
  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(doc));
  Render(screen, doc);
  screen.Print();

}

