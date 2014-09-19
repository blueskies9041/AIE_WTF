# AIEFramework

The AIE C++ OpenGL Framework, used by Advanced Diploma and Degree students. This repo is in constant flux and improvement. Differences may exist between this code-base and class tutorials.

## Purpose

  - An *eventually* cross-platform (Windows, OSX, Linux) wrapper for a real-time OpenGL game loop.
  - OpenGL functionality should remain bare for students to learn as much as possible.
  - The ability to load textures and 3D models will be provided, but loaded model data will
    not automatically create OpenGL resources.
  - A helper class for easily drawing debug 2D/3D "widgets" will be provided so that basic
    math ideas can be demonstrated, along with A.I. entities and physics, without the need to
    load a model.

## Dependencies

  This project depends on the following 3rd-party libraries:

  - GLEW (for managing OpenGL extensions)
  - GLFW (for managing basic OpenGL window and controls)
  - GLM (for mathematics)
  - STB (for simple image loading)
  - FBX SDK 2015.1 (for the optional FBXLoader library for loading FBX models)

## Quick Setup

1. Clone the repository to your workstation.
2. Clone the submodules and build them where applicable.
3. Configure the FBXLoader project's Environment Variables property sheet to point to the location of the FBX SDK on your workstation.
4. Build the AIEFramework solution.

For more information or help, see the Github wiki.

### Visual Studio Project Template

Within the /tools/ folder there are zip files that contain project templates for Visual Studio 2012/13.

These should be placed within the Visual Studio folder located within your user Documents folder.

i.e. for Visual Studio 2013 on a typical install:
C:\Users\<username>\Documents\Visual Studio 2013\Templates\ProjectTemplates\Visual C++ Project\

With the project templates you are able to add a new pre-made project to the AIE framework by simply opening the AIE solution and selecting "Add Project" and choosing the AIEApplication project type.
