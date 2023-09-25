#include <stdio.h>
#include <string.h>

#include "snake_utils.h"
#include "state.h"

int main(int argc, char* argv[]) {
  bool io_stdin = false;
  char* in_filename = NULL;
  char* out_filename = NULL;
  game_state_t* state = NULL;

  // Parse arguments
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
      if (io_stdin) {
        fprintf(stderr, "Usage: %s [-i filename | --stdin] [-o filename]\n", argv[0]);
        return 1;
      }
      in_filename = argv[i + 1];
      i++;
      continue;
    } else if (strcmp(argv[i], "--stdin") == 0) {
      if (in_filename != NULL) {
        fprintf(stderr, "Usage: %s [-i filename | --stdin] [-o filename]\n", argv[0]);
        return 1;
      }
      io_stdin = true;
      continue;
    }
    if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
      out_filename = argv[i + 1];
      i++;
      continue;
    }
    fprintf(stderr, "Usage: %s [-i filename | --stdin] [-o filename]\n", argv[0]);
    return 1;
  }

  // Do not modify anything above this line.

  /* Task 7 */

  // Read board from file, or create default board
  if (in_filename != NULL) {
    FILE* infile = fopen(in_filename, "r");
    if (infile == NULL) {
      fprintf(stderr, "Error: File '%s' not found.\n", in_filename);
      return -1;
    }
    state = read_state(infile);
    fclose(infile);

    // Check if the state is NULL (i.e., error in reading the state)
    if (state == NULL) {
      fprintf(stderr, "Error: Failed to read the state from file '%s'.\n", in_filename);
      return -1;
    }

    // Initialize the snakes and their body segments
    initialize_snakes(state);
  } else if (io_stdin) {
    state = read_state(stdin);
    if (state == NULL) {
      fprintf(stderr, "Error: Failed to read the state from stdin.\n");
      return -1;
    }

    // Initialize the snakes and their body segments
    initialize_snakes(state);
  } else {
    // Create default state
    state = create_default_state();
  }

  // Update state. Use the deterministic_food function to add food.
  deterministic_food(state);

  // Write updated board to file or stdout
  if (out_filename != NULL) {
    FILE* outfile = fopen(out_filename, "w");
    if (outfile == NULL) {
      fprintf(stderr, "Error: Failed to open the output file '%s'.\n", out_filename);
      free_state(state);
      return -1;
    }
    write_state(outfile, state);
    fclose(outfile);
  } else {
    write_state(stdout, state);
  }

  // Free the state
  free_state(state);

  return 0;
}
