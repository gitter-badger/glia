# glia

## Dependencies

### mstch
```bash
cd /tmp
git clone https://github.com/no1msd/mstch.git
cd mstch
mkdir build
cd build
cmake ..
make
sudo make install
```

### rapidjson
```bash
cd /tmp
git clone https://github.com/miloyip/rapidjson.git
cd rapidjson
git submodule update --init
mkdir build
cd build
cmake ..
make
sudo make install
```

### Boost
```bash
cd /tmp
sudo apt-get install build-essential g++ python-dev autotools-dev libicu-dev libbz2-dev -y
wget https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.gz
tar xvfz boost_1_64_0.tar.gz
cd boost_1_64_0
sudo ./bootstrap.sh
sudo ./b2 --with=all -j 4 install
```

### GRPC
```bash
cd /tmp
git clone https://github.com/grpc/grpc
cd grpc
git submodule update --init
make
sudo make install
```