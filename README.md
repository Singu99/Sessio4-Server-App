# Epidemic replicaton monitor
Simple desktop app that helps monitor the state of the nodes of the epidemic replication in an interactive and visual way. 

## Build
There is a provided CMakeLists that should compile the program whitout issues. The program needs to be compiled using `MSVC` compiler. The build and execution of the program have been tested as well with Visual Studio Code (using CMake Tools extension) and CLion IDEs. 

It is very important to make sure that the `imgui.ini` file inside *window_layout* can be found by the executable. There is a post build command in the cmake that copies that file next to the executable but some IDEs change the working directory of the project. 

## Dependencies

The project has all the build in dependencies in the dependencies folder.

### List of dependencies:

-   **Rendering graphics**: Opengl3, glfw, glad, imgui
-   **Math library**: glm
-   **Web socket server**: Crow
    -   **Crow**: It has Thread and Regex dependencies from boost library.

## Notes
The Epidemic replication program is located in the following repository: 
-   [Epidemic Replication](https://github.com/MarcEspuna/ReplicacioEpidemica)

Remember to open this server first before opening the Epidemic Replication program in order to allow both to connect correctly.

