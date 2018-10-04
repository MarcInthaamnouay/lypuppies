# Lypuppies

Just a small test project which goal is to try binding C to NodeJS using Node experimental N-API

# Functionnality

There are 2 C file that are compile into a static library
which are later used by n-api in order to expose the methods of the lypuppies lib

# Bindings

The binding is using n-api. There are good starter tutorial on medium as well as some n-api usage example on the node repository. You can also check out my code (not the best C code you will ever see though...).

# JS method exposed

- GenerateUniquePuppy
- PuppyBark
- GetPuppyExpectedLife

# Install & Usage

The repo contains some C file (lib & bindings) as well as a makefile which compile the lib sources into a static lib. Futhermore the repo contains a binding.gyp which is used by node-gyp to build the module

- Clone the repo
- Run : ``` npm install ```
- Run : ``` make ```
- Run : ``` npm run build ```

# Tests

Some test are available on the folder test
Use the cmd: ``` npm run test ``` in order to run the tests.

