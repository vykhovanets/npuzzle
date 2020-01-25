  // auto count_inv = [&](int x, int y, auto first_state, int size) {
  //   int num{first_state.at(y).at(x)};
  //   int invs{0};
  //   int k{x + y * size};

  //   while (k < size * size) {
  //     x = k % size;
  //     y = k / size;
  //     if (first_state.at(y).at(x) < num)
  //       invs++;
  //     k++;
  //   }

// ---------- external


private bool IsPuzzleSolvable(int[] puzzle)
{
    int zeroPosition = -1;
    int inversionsNumber = 0;
    for (int i = 0; i < puzzle.Length; i++)
    {
        if (puzzle[i] == 0)
            continue;
        inversionsNumber += CountInversions(puzzle, puzzle[i], i);
    }
    int idx = Array.IndexOf(puzzle, 0);
    zeroPosition = (int)(idx / PuzzleSize) + 1;
    if (PuzzleSize % 2 == 0)
    {   
        if ((PuzzleSize / 2) % 2 == 0 && 
          ((zeroPosition % 2 == 1 && inversionsNumber % 2 == 0) || 
            (zeroPosition % 2 == 0 && inversionsNumber % 2 == 1)))
            return true;
        else if ((PuzzleSize / 2) % 2 == 1 && 
          zeroPosition % 2 == inversionsNumber % 2 && 
          zeroPosition % 2 != zeroPosition-1)
            return true;
        else
            return false;
    }
    else
        return (inversionsNumber % 2 == 0);
}




private int CountInversions(int[] inputPuzzle, int currElem, int elemIdx)
{
                                                                     // input_puzzle = first_state_to_1d_array
    int correctRow = Array.IndexOf(Solution, currElem) / PuzzleSize; // 
    int correctCol = Array.IndexOf(Solution, currElem) % PuzzleSize; // int x { final_state[currElem].x };
    int inversions = 0;                                              // int invs;

    for (int i = elemIdx +1; i < inputPuzzle.Length; i++)
    {
        if (inputPuzzle[i] == 0)
            continue;
        int currentElemCorrectRow = Array.IndexOf(Solution, inputPuzzle[i]) / PuzzleSize;
        int currentElemCorrectCol = Array.IndexOf(Solution, inputPuzzle[i]) % PuzzleSize;
        if (currentElemCorrectRow < correctRow || (currentElemCorrectRow == correctRow && currentElemCorrectCol < correctCol))
            inversions++;
    }
    return inversions;
}




row == y
col == x





























