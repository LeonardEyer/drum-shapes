# String~

# Setup
Clone and initialize the submodules
````
git clone https://github.com/LeonardEyer/drum-shapes
cd drum-shapes
git submodule update --init --recursive
````

# Compile
```
mkdir build
cd build
cmake ..
make
```

# Use

The built externals are located [here](externals). Simply open the corresponding ``<name>-help.pd`` file using PureData
