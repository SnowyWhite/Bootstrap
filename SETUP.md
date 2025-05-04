# Setup

Below is a summary of the steps required for initializing the project, configuring build environments,  
and managing build settings.

## 🛠️ Project Initialization

Start by creating a new, empty project structure:

```shell
bdep new -t empty bootstrap
cd bootstrap
```

Next, add two packages:
- A library that will contain the business logic
- An executable that can be used to test the library

```shell
bdep new --package -l c++ -t lib libbootstrap
bdep new --package -l c++ -t exe bootstrap
```

## ⚙️ Add Build Configurations

### MinGW (Default)

Initialize a build configuration for MinGW:

```shell
bdep init -C -@mingw cc config.cxx=g++ config.cc.compiledb=./
```

### MSVC

To add MSVC support, open a Visual Studio Developer Command Prompt and run:

```shell
bdep init -C -@msvc cc config.cxx=cl config.cc.compiledb=./ config.config.hermetic=true
```

> 💡 Note: This defaults to an `x86_64` target. Use the `x86` Developer Command Prompt if you need 32-bit.  

The `config.config.hermetic=true` variable ensures the configuration is portable.  
This means that it can be used from outside a Visual Studio Developer command Prompt.

## 🧱 Building the Project

- To build the **default configuration**:

```shell
b
```

- To build a **specific configuration**:

```shell
bdep update -@mingw
bdep update -@msvc
```

- To build **all configurations** at once:

```shell
bdep update -a
```

## 🔧 Managing Configurations

### Remove Configuration

```shell
bdep deinit -@msvc
bdep config remove -@msvc
```

### Edit a Configuration

Change the C++ compiler:

```shell
b config.cxx=cl
```

Set compile options (e.g., debug symbols):

```shell
b config.cxx.coptions=-g
```

> ⚠️ These overrides apply only to the current build invocation.

For example:

```shell
b config.cxx.coptions=-O3
b
```

...will first build with `-O3`, and then again with the previously set `-g`.

### Saving Configuration Changes

To persist changes in `build/config.build`, `cd` into the source directory and use:

```shell
b configure config.cxx.coptions=-g
```

Or, from outside the source directory:

```shell
b configure: 'bootstrap/@bootstrap-mingw/' config.cxx.coptions=-g config.import.libbootstrap=libbootstrap/
```

### Cleaning Up

From within the source directory:

```shell
b disfigure
```

Or, from outside the source directory:

```shell
b disfigure: 'bootstrap/@bootstrap-mingw/'
```

To reset a configuration to its default:

```shell
b configure config.config.disfigure=config.cxx
```