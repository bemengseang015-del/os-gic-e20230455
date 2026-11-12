# OS Lab 2 — Linux Navigation & File Management

## 1. Student Information

- **Student:** Mengseang
- **Course:** Operating Systems
- **Lab:** Lab 2 — Linux Navigation & File Management
- **Username:** `gic-be-mengseang`
- **Environment:** Ubuntu 26.04.1 LTS
- **Workspace:** `~/oslab-work/lab2`

## 2. Lab Objectives

The objectives of this lab are to:

- Understand Linux directory navigation.
- Practice creating directories and files.
- Use relative and absolute paths.
- Move and copy files between directories.
- Understand filenames containing spaces.
- Identify and correct common path errors.
- Use Linux commands to inspect directory structures.

## 3. Personal Configuration

| Variable | Value |
|---|---|
| First file | `budget 2026.txt` |
| Second file | `audit notes.txt` |
| Owner department | `Legal` |
| Reader department | `Marketing` |
| Third department | `Support` |
| First amount | `268` |
| Second amount | `330` |

## 4. Environment Setup

The lab workspace was initialized using:

```bash
export OSLAB_WORKSPACE="$HOME/oslab-work"
oslab start lab2
cd "$OSLAB_WORKSPACE/lab2"
mkdir -p evidence
oslab values lab2
```

## 5. Core 1 — Directory Creation

Created the required company directory structure:

```bash
mkdir -p "TechCorp/$owner/archive" \
         "TechCorp/$reader" \
         "TechCorp/$third"
```

Verified the directory structure using:

```bash
find TechCorp -type d | sort
```

Expected directories:

```text
TechCorp
TechCorp/Legal
TechCorp/Legal/archive
TechCorp/Marketing
TechCorp/Support
```

**Result:** Verified successfully.

## 6. Core 2 — Moving and Copying Files

### 6.1 Move the first file using a relative path

```bash
mv -- "incoming/$file1" reports/
```

### 6.2 Move the second file using absolute paths

```bash
mv -- "$OSLAB_WORKSPACE/lab2/incoming/$file2" \
      "$OSLAB_WORKSPACE/lab2/reports/"
```

### 6.3 Copy both report files to Legal

```bash
cp -- "reports/$file1" "reports/$file2" "TechCorp/$owner/"
```

### 6.4 Archive the original first file

```bash
cp -- "reports/$file1" \
      "TechCorp/$owner/archive/first-original.txt"
```

### 6.5 Read a report from Marketing

Relative path:

```bash
cat "../../reports/$file1"
```

Absolute path:

```bash
cat "$OSLAB_WORKSPACE/lab2/reports/$file1"
```

Both commands were verified and displayed:

```text
amount,268
```

**Result:** Verified successfully.

## 7. Core 3 — Comparing Files and Correcting Path Errors

### 7.1 Compare the copied files

```bash
cmp -- "reports/$file1" "TechCorp/$owner/$file1"
cmp -- "reports/$file2" "TechCorp/$owner/$file2"
```

Both comparisons returned no output, confirming identical contents.

### 7.2 Demonstrate an incorrect relative path

From `TechCorp/Marketing`, the following command produced a file-not-found error:

```bash
cat "reports/budget 2026.txt"
```

### 7.3 Correct the path

```bash
cat "../../reports/budget 2026.txt"
```

The corrected command displayed:

```text
amount,268
```

### 7.4 Generate the file tree

```bash
find incoming reports TechCorp -type f | sort | tee evidence/tree.txt
```

**Result:** Verified successfully.

## 8. Evidence Files

The `evidence/` directory contains:

| File | Description |
|---|---|
| `paths.txt` | Move, copy, relative-path, absolute-path, and error-correction evidence |
| `tree.txt` | Sorted directory file listing |
| `checkpoint.txt` | Practical checkpoint output — pending completion |

## 9. Live Checkpoint

The four checkpoint questions were answered and submitted to the instructor.

The practical file-reading evidence has not yet been saved successfully. Therefore, `evidence/checkpoint.txt` remains empty and the checkpoint milestone is pending.

## 10. Lab Verification

The latest official checker result:

```text
PASS: both files were moved into reports/ with their contents
PASS: TechCorp/Legal/ holds identical copies
PASS: archive/first-original.txt is a copy of your first file
PASS: evidence/paths.txt records a relative and an absolute path
PASS: evidence/paths.txt has your Error: line and a Fix: path
milestones: 5/6
```

**Current verified result: 5/6 milestones.**

## 11. Lessons Learned

Through this lab, I practiced:

1. Navigating Linux directories using `cd` and `pwd`.
2. Listing files with `ls` and `find`.
3. Creating directories using `mkdir`.
4. Moving files using `mv`.
5. Copying files using `cp`.
6. Reading file contents using `cat`.
7. Using relative and absolute paths.
8. Handling filenames containing spaces with quotes.
9. Comparing files using `cmp`.
10. Finding and correcting incorrect file paths.

## 12. Conclusion

This lab provided practical experience with Linux navigation and file management. I learned how relative and absolute paths work, how to move and copy files, and how to troubleshoot common path errors.

The five core milestones verified successfully. The practical checkpoint evidence remains to be completed.
