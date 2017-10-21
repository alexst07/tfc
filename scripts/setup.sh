#!/usr/bin/env shpp

RED = "\033[0;31m"
GREEN = "\033[0;32m"
CYAN = "\033[1;36m"
WHITE = "\033[1;37m"
YELLOW = "\033[1;33m"

# main project path
PROJECT_PATH = __path__ + "/../"
THIRD_PARTY_PATH = PROJECT_PATH + "third-party/"
GOOGLE_PATH = THIRD_PARTY_PATH + "google/"

#
# print with color
#
func printc(color, args...) {
  print(color, ...args, "\033[0m")
}

#
# print the error and exit
#
func fail(args...) {
  printc(RED, ...args)
  exit 1
}

#
# execute a function in a given path
#
func on_path(dir, f, args...) {
  if !path(dir).exists() {
    printc(RED, "path: '" + dir + "' not exisits")
    exit 1
  }

  p = $(pwd)
  cd ${dir}
  f(...args)
  cd ${p}
}

#
# Download tensorflow and get proto files
#
func get_tf_proto_files() {
  if path(GOOGLE_PATH + "tensorflow").exists() {
    printc(YELLOW, "tensorflow already installed")
    return
  }

  on_path("/tmp", func() {
    try {
      git clone https://github.com/tensorflow/tensorflow
    } catch InvalidCmdException {
      fail("git not installed")
    }

    cd tensorflow
    find \. -type f  ! -name "*.proto" -delete
    cd ..
    cp -r tensorflow ${GOOGLE_PATH}
    printc(GREEN, "proto files copied")
  })
}

#
# install protobuf on third party
#
func install_protobuf() {
  if path(GOOGLE_PATH + "protobuf").exists() {
    printc(YELLOW, "protobuf already installed")
    return
  }

  on_path("/tmp", func() {
    try {
      git clone https://github.com/google/protobuf.git
    } catch InvalidCmdException {
      fail("git not installed")
    }
  })

  on_path("/tmp/protobuf", func() {
    git checkout v3.4.1
    ./autogen.sh
    protobuf_path = GOOGLE_PATH + "protobuf"
    mkdir ${protobuf_path}
    ./configure --prefix=${protobuf_path}
    make
    make check
    make install
    printc(GREEN, "protobuf installed")
  })
}

#
# compile tensorflow proto files
#
func compile_proto() {
  on_path(GOOGLE_PATH + "tensorflow", func() {
    ${GOOGLE_PATH + "protobuf/bin/protoc"} --cpp_out=${GOOGLE_PATH + "tensorflow"} $@{%%*.proto%}
    printc(GREEN, "proto files compiled")
  })
}

#
# main function
#
func main() {
  on_path(PROJECT_PATH, func() {
    # create google thrid-party
    if !path(GOOGLE_PATH).exists() {
      mkdir -p third-party/google
      printc(GREEN, "third-party created")
    }
  })

  get_tf_proto_files()
  install_protobuf()
  compile_proto()
}

if __main__ {
  main()
}
