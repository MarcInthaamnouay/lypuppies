# Lypuppies (WIP)

Just a small test project which goal is to try binding C to NodeJS using Node experimental N-API

# Functionnality

There are 2 C file that are compile into a static library
which are later used by n-api in order to expose the methods of the lypuppies lib

# Bindings

The binding is using n-api some good tutorials are available on medium...

# JS method exposed

- GenerateUniquePuppy
- WIP

# Install & Usage

The repo contains some C file (lib & bindings) as well as a makefile which compile the lib sources into a static lib. Futhermore the repo contains a binding.gyp which is used by node-gyp to build the module

- Clone the repo
- Run : ``` npm install ```
- Run : ``` make ```
- Run : ``` npm run build ```

# Tests

Some test are available on the folder test
Use the cmd: ``` npm run test ``` in order to run the tests.

