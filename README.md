# OpenCloud

Dark Cloud 1 and 2 open reimplementation.

## Building
Currently the build is MSBuild and Windows only. There are plans for CMAKE/Linux down the road.

1. Open `OpenCloud.sln`
2. Right click the `opencloud2` project and select `Set as Startup Project`
3. Build or Debug

## Tools

- [Ghidra](https://github.com/NationalSecurityAgency/ghidra/releases) and [EE Ghidra Plugin](https://github.com/beardypig/ghidra-emotionengine/releases)

## Setup Ghidra

1. Download [Ghidra 9.2.2](https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_9.2.3_build/ghidra_9.2.3_PUBLIC_20210325.zip) (for ee plugin compatibility)
2. Accept the terms and conditions
3. In the main window (the one that had the projects dropdown) select `File` and then `Install Extensions...`
4. Select the `zip` file from the [EE Ghidra plugin download page](https://github.com/beardypig/ghidra-emotionengine/releases/download/v1.6.0/ghidra_9.2.2_PUBLIC_20210226_ghidra-emotionengine.zip)
5. Create a new project.
6. Drag and drop the Dark Cloud executable into the project.
7. Double click the exe in the project dropdown.
8. Ghidra will ask to analyze the project, before doing so select the `Demanagler GNU` Analyzer and check `Use Deprecated Demangler`
9. Click analyze.

## Disclaimer
Open Cloud is in no way affliated with Level-5 or Sony Computer Entertainment or their registered trademarks.
Open Cloud is a reverse-eningeering and educational project and does not and will not contain any art, sound, or any other copywritten material from the Dark Cloud games. Any such pull requests, commits, or other postings on this Github which contain such materials will be refused and deleted on sight.
