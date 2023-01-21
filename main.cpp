#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<double>> matrix;

void printEquations()
{
    int n = matrix.size();
    for (int i = 0; i < n; i++)
    {
        cout << "Eq #" << i + 1 << ": ";

        for (int j = 0; j < n; j++)
        {

            if (j == 0)
            {
                if (matrix[i][j] < 0)
                    cout << "-";
            }
            else if (matrix[i][j] < 0)
                cout << "- ";
            else
                cout << "+ ";

            cout << abs(matrix[i][j]) << "*x" << j + 1 << " ";
        }
        cout << "= " << matrix[i][n] << endl;
    }
    cout << endl;
}

// returns true if the input is valid
bool getEquation()
{
    matrix.clear();
    cout << "Type linear equations in augmented matrix notatation: a1 a2 a3 ... aN d" << endl;
    cout << "          Where a1 ... aN are coefficients and d is the constant" << endl;
    cout << "Type END to finish entering equation" << endl;

    string line;
    int cnt = 1;
    // take the input
    while (true)
    {
        cout << "Eq #" << cnt++ << ": ";
        getline(cin, line);
        if (line == "END")
            break;

        // parse the input using stringstream
        stringstream ss(line);
        vector<double> row;
        double num;
        while (ss >> num)
        { // while there is a number in the line
            row.push_back(num);
        }
        matrix.push_back(row);
    }

    // check if the input is valid
    int n = matrix.size();
    if (n == 0)
    {
        cout << "No equation entered" << endl;
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        if (matrix[i].size() != n + 1)
        {
            cout << "ERROR:\n";
            cout << "Number of equations: " << n << endl;
            cout << "Equation #" << i + 1 << " is invalid" << endl;
            cout << "There should be exactly " << n << " cofficient and 1 constant." << endl;
            cout << "You entered " << matrix[i].size() << " numbers in total." << endl;
            cout << "Invalid input" << endl;
            return false;
        }
    }

    return true;
}

bool solve()
{

    int n = matrix.size();

    for (int i = 0; i < n; i++)
    {

        // find the maximum element in the i-th column (partial pivoting)
        int mx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (abs(matrix[j][i]) > abs(matrix[mx][i]))
                mx = j;
        }

        // max element is 0, matrix can not be solved
        if (abs(matrix[mx][i]) < 1e-9)
        {
            cout << "\nThe system is singular! CAN NOT BE SOLVED!"; return false;
        }

        // swap the row with the max element in the i-th column
        if (mx != i)
            swap(matrix[i], matrix[mx]);

        // forwards elimination
        for (int j = i + 1; j < n; j++)
        {
            double c = matrix[j][i] / matrix[i][i];
            for (int k = i; k < n + 1; k++)
            {
                matrix[j][k] -= matrix[i][k] * c;
            }
        }
    }

    // backwards substitution
    for (int i = n - 1; i >= 0; i--)
    {
        double c = matrix[i][i];
        if (abs(c) < 1e-9)
        {
            cout << "\nThe system has no unique solution!";
            return false;
        }

        for (int j = i; j < n + 1; j++)
        {
            matrix[i][j] /= c;
        }
        for (int j = i - 1; j >= 0; j--)
        {
            c = matrix[j][i];
            for (int k = i; k < n + 1; k++)
            {
                matrix[j][k] -= matrix[i][k] * c;
            }
        }
    }

    // print the solution
    cout << "\nResult is: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x" << i + 1 << " = " << matrix[i][n] << endl;
    }

    return 1;
}

int main()
{

    string s;

    while (true)
    {
        if (!getEquation())
        {
            cout << "\nPress ENTER to continue..." << endl;
            getline(cin, s);
            continue;
        }

        cout << "You entered the following equations:" << endl;
        printEquations();

        cout << "\nPress ENTER to continue..." << endl;
        getline(cin, s);

        solve();

        cout << "\nPress ENTER to continue..." << endl;
        getline(cin, s);

        cout << "Proceed to solve another system? (y/n): ";
        getline(cin, s);

        if (s != "y")
            break;
    }
}
