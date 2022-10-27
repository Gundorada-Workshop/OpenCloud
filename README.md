# OpenCloud

Dark Cloud 1 and 2 open reimplementation.

## Tools

- [Ghidra](https://github.com/NationalSecurityAgency/ghidra/releases) and [EE Ghidra Plugin](https://github.com/beardypig/ghidra-emotionengine/releases)

## Setup Ghidra

1. Download Ghidra 9.2.2 (for ee plugin compatibility)
2. Accept the terms and conditions
3. In the main window (the one that had the projects dropdown) select `File` and then `Install Extensions...`
4. Select the `zip` file from the EE Ghidra pluging download page
5. Create a new project.
6. Drag and drop the Dark Cloud executable into the project.
7. Double click the exe in the project dropdown.
8. Ghidra will ask to analyze the project, before doing so select the `Demanagler GNU` Analyzer and check `Use Deprecated Demangler`
9. Click analyze.
