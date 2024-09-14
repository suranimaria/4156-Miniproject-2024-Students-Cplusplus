# Miniproject Individual Assignment - L1

## Part 1. Code Clean-Up

Follow the set-up steps from the assignment instructions (**Reminder** to update paths in `CMakeLists.txt` for external libraries)

1. **Navigate to the build directory**:
    ```shell
    cd build
    ```

2. **Run CMake to generate the build files**:
    ```shell
    cmake ..
    ```

3. **Compile the project**:
    ```shell
    make
    ```

4. **Run `cpplint` to check for Google C++ Style Guide compliance**:
    ```shell
    make cpplint
    ```

## Part 2. Testsuite & Branch Coverage

`lcov` is used to measure branch and line coverage for the test suite.

### Steps to generate code coverage:

1. **Install `lcov`** (assumes macOS and Homebrew):
    ```shell
    brew install lcov  
    ```

2. **Build and run the tests**:
    ```shell
    cd build
    cmake ..
    make
    ./IndividualMiniprojectTests
    ```

   *Note*: Running the tests is required to generate `.gcda` and `.gcno` files which contain information about the execution of the program during test runs. (essential for measuring code coverage)

3. **Generate the coverage report**:
    Navigate to the directory containing coverage data (`.gcda` and `.gcno` files):
    ```shell
    cd CMakeFiles/IndividualMiniprojectTests.dir/src
    ```

4. **Capture the total coverage information**:
    ```shell
    lcov --filter range --ignore-errors inconsistent --capture --directory . -o totalCoverage.info
    ```

5. **Filter out irrelevant paths (system directories / libraries ..)**:
    ```shell
    lcov --filter range --ignore-errors inconsistent --remove totalCoverage.info "/usr*" "include/" -o filteredCoverage.info
    ```

6. **Generate an HTML report of the filtered coverage**:
    ```shell
    genhtml --filter range --ignore-errors inconsistent filteredCoverage.info --output-directory branch_coverage
    ```

7. **View the report**:
    Open the report in browser:
    ```shell
    open branch_coverage/index.html
    ```

    Clicking on the `src` folder will display coverage details for each file. The top-right corner will show the overall coverage percentage.


## Part 3. Static Code Analysis

`clang-tidy` is used for performing static analysis.

### Steps to run static analysis using `clang-tidy`:

1. **Install LLVM and Clang tools** (assumes macOS and Homebrew):
    ```shell
    brew install llvm
    brew --prefix llvm 
    // copy this path and paste it below
    echo 'export PATH="YOUR_PATH_TO_LLVM:$PATH"' >> ~/.zshrc 
    source ~/.zshrc
    ```

2. **Navigate to the build directory**:
    ```shell
    cd build
    ```

3. **Generate build files with the flag to generate `compile_commands.json` enabled**:
    ```shell
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=true ..
    ```

4. **Run `clang-tidy` with the generated compile commands**:
    ```shell
    cd ..
    clang-tidy src/* include/* -p build/compile_commands.json > clang-tidy-results.txt
    ```

    The output file `clang-tidy-results.txt` will contain the results of the static analysis. If the file is empty, no bugs or issues were found based on the enabled checks.

   *Note*: The checks enabled for `clang-tidy` are defined in the `.clang-tidy` file. In this case, only specific checks for static analysis are enabled to avoid unnecessary noise.


