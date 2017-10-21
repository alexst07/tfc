func exist_cmd(name) {
  c = $(whereis ${name})

  arr = string(c).trim().split(":")

  if arr[1] == "" {
    return false
  }

  return true
}

lint_path = __path__ + "/../build/"

if !path.exists(lint_path + "/" + "cpplint.py") {
  if exist_cmd("wget") {
    echo output path: ${lint_path}
    wget -P ${lint_path} https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py
  }
}

lint_exec = lint_path + "cpplint.py"
chmod +x ${lint_exec}

for file in $(find ../src) {
  if file.ends_with(".cc") || file.ends_with(".h") {
    print("lint file: ", file)
    ${lint_exec} ${file}
  }
}
