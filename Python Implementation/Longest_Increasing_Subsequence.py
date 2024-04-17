import sys


def f(idx, prev_idx, n, a, dp):
    if idx == n:
        return 0

    if dp[idx][prev_idx + 1] != -1:
        return dp[idx][prev_idx + 1]

    notTake = 0 + f(idx + 1, prev_idx, n, a, dp)
    take = -sys.maxsize - 1
    if prev_idx == -1 or a[idx] > a[prev_idx]:
        take = 1 + f(idx + 1, idx, n, a, dp)

    dp[idx][prev_idx + 1] = max(take, notTake)
    return dp[idx][prev_idx + 1]


def longest_subsequence(n, a):
    # Check if the array is strictly decreasing
    is_decreasing = all(a[i] > a[i + 1] for i in range(n - 1))
    if is_decreasing:
        return 0

    dp = [[-1 for _ in range(n + 1)] for _ in range(n + 1)]
    return f(0, -1, n, a, dp)


def main():
    file_path = "C:\\Users\\pavi2\\OneDrive\\Desktop\\input1.txt"
    try:
        with open(file_path, "r") as file:
            num_test_cases_str = file.readline().strip()
            if not num_test_cases_str:
                print("Error: Number of test cases not specified.")
                return

            num_test_cases = int(num_test_cases_str)

            for _ in range(num_test_cases):
                # Skip empty line between test cases
                file.readline()

                n_str = file.readline().strip()
                if not n_str:
                    print("Error: Empty line encountered while reading the size of the array.")
                    continue

                n = int(n_str)
                arr_str = file.readline().strip()
                if not arr_str:
                    print("Error: Expected array data for test case but found empty line.")
                    continue

                arr = list(map(int, arr_str.split()))
                lis_length = longest_subsequence(n, arr)
                print("Length of the Longest Increasing Subsequence:", lis_length)
    except FileNotFoundError:
        print("Error: File not found:", file_path)
    except ValueError as e:
        print("Error:", e)


if __name__ == "__main__":
    main()
