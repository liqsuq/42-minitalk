#!/bin/bash

FG='\e[32m'
NC='\e[0m'

CLIENT="./client"

usage() {
    echo "Usage: $0 [-b] <PID>"
}

while getopts b OPT
do
    case $OPT in
        b)  CLIENT="./client_bonus"; shift;;
        *)  usage;;
    esac
done

if [ $# -ne 1 ]; then
    echo "Usage: $0 [-b] <PID>"
    exit 1
fi

if [ ! -f ./client ]; then
    echo "client not found"
    exit 1
fi

if ! [[ $1 =~ ^[0-9]+$ ]]; then
    echo "Invalid PID"
    exit 1
fi

measure_time() {
    local start_time=$1
    local end_time=$2
    echo "$(echo "$end_time - $start_time"|bc) seconds"
}

run_test() {
    local pid=$1
    local message=$2
    local start_time=$(date +%s.%6N)
    ./client $pid "$message" &> /dev/null
    local retval=$?
    local end_time=$(date +%s.%6N)
    if [ $retval -eq 0 ]; then
        echo "⭕ OK!!! ($(measure_time $start_time $end_time))"
    else
        echo "❌ NG..."
    fi
}

messages=(
"Hello World"
"1234567890"
"~!@#$%^&*()_+-={}|[]\:;<>?,./"
"こんにちは世界"
"你好世界"
"안녕하세요세계"
"¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿"
"Ⅰ Ⅱ Ⅲ Ⅳ Ⅴ Ⅵ Ⅶ Ⅷ Ⅸ Ⅹ Ⅺ Ⅻ"
"① ② ③ ④ ⑤ ⑥ ⑦ ⑧ ⑨ ⑩"
"㋀㋁㋂㋃㋄㋅㋆㋇㋈㋉㋊㋋"
"㌰㌰㌠㌍㌧㌧㌨"
"🤣😍🤗🤔🥺😳😭🙂😊😩"
"🎉🎊🎉🎊🎂🥳🎊🎉🎊🎉"
)

for message in "${messages[@]}"; do
    echo -e "${FG}Message: ${NC}$message"
    run_test $1 "$message"
done

echo "================================"
echo -e "${FG}Speed Test (100 characters):${NC}"
run_test $1 "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean "
echo -e "${FG}Speed Test (1000 characters):${NC}"
run_test $1 "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Etiam rhoncus. Maecenas tempus, tellus eget condimentum rhoncus, sem quam semper libero, sit amet adipiscing sem neque sed ipsum. "
