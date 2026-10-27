# Boyer-Moore String Search: Bad-Character Heuristic Only

> **Graduate coursework (2022), archived.** This repo is kept for reference and is not maintained.

This program finds every occurrence of a pattern in a text file using the **bad-character rule** of Boyer-Moore. The text file is `Sample.txt`, a 406,666-byte string of lower-case DNA bases (`a`, `c`, `g`, `t`) and spaces. The program reports each match offset and how long the search took in microseconds.

The companion repo, [TraditionalBoyerMoore](https://github.com/HariVenkataKrishnaKotha/TraditionalBoyerMoore), uses the same `Sample.txt` and adds the good-suffix rule.

## The algorithm

Boyer-Moore lines the pattern up against the text and compares characters **from right to left**. The bad-character heuristic first builds a 256-entry table that holds the **last position** of each byte in the pattern, or -1 if the byte does not occur. Suppose a mismatch happens at pattern index `j` on text character `c`. The pattern then shifts right by `max(1, j - last[c])`. That lines the mismatched text character up with its last occurrence in the pattern, or moves the pattern past it entirely when `c` does not occur in the pattern.

After a full match, the program shifts so that the character just after the window lines up with its last occurrence in the pattern, and it keeps searching. Every match is reported.

For long patterns over a large alphabet, this skips most of the text. For a 4-letter alphabet like DNA, the shifts are short.

## Build

The source file is `BayerMoore.cpp`. That spelling is the original file name.

```bash
g++ -std=c++17 BayerMoore.cpp -o BayerMoore
```

*(not verified: g++ is not installed on the test machine. The code calls `max` without including `<algorithm>`, so add that include if your compiler complains.)*

With MSVC, or by opening `BayerMoore.sln` in Visual Studio:

```bat
cl /std:c++17 /EHsc BayerMoore.cpp /Fe:BayerMoore.exe
```

**Verified on 2026-10-27:** MSVC 14.51 (`cl /std:c++17 /EHsc /W4`) compiled it successfully. It gave two C4267 `size_t`-to-`int` warnings.

## Run

Run the program from the folder that contains `Sample.txt`, because the file name is hard-coded. Type one pattern per line.

```bash
./BayerMoore
```

Sample output, captured from the MSVC build. Timings vary.

```
gtgtcaatgtaaattcg
The pattern found @ 65

Pattern : gtgtcaatgtaaattcg

Elapsed time in micro seconds: 957 micro seconds
acagtatgg
The pattern found @ 0
The pattern found @ 373037

Pattern : acagtatgg

Elapsed time in micro seconds: 616 micro seconds
```

The program loops forever, so press **Ctrl+C** to quit.

## Known issues

- **Empty input loops forever.** If you enter an empty line, or input reaches end-of-file (for example with piped input), the pattern is empty. The program then reports a "match" at every offset and repeats endlessly. This was observed when testing with piped input.
- The 256-entry table is indexed with a plain `char`. Bytes above 127 give a negative index, which is an out-of-bounds read on non-ASCII input. The fix is to cast to `unsigned char`.
- The input file is hard-coded to `Sample.txt`, and there is no way to exit other than Ctrl+C.

Graduate coursework (2022), archived.
