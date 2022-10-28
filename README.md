# OpenCloud

Dark Cloud 1 and 2 open reimplementation.

## Tools

- [Ghidra](https://github.com/NationalSecurityAgency/ghidra/releases) and [EE Ghidra Plugin](https://github.com/beardypig/ghidra-emotionengine/releases)

## Setup Ghidra

1. Download Ghidra 9.2.2 (for ee plugin compatibility)
2. Accept the terms and conditions
3. In the main window (the one that had the projects dropdown) select `File` and then `Install Extensions...`
4. Select the `zip` file from the EE Ghidra plugin download page
5. Create a new project.
6. Drag and drop the Dark Cloud executable into the project.
7. Double click the exe in the project dropdown.
8. Ghidra will ask to analyze the project, before doing so select the `Demanagler GNU` Analyzer and check `Use Deprecated Demangler`
9. Click analyze.

## Disclaimer
Open Cloud is in no way affliated with Level-5 or Sony Computer Entertainment or their registered trademarks.
Open Cloud is a reverse-eningeering and educational project and does not and will not contain any art, sound, or any other copywritten material from the Dark Cloud games. Any such pull requests, commits, or other postings on this Github which contain such materials will be refused and deleted on sight.
