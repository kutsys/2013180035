# ~/.bashrc: 비로그인 쉘들에 대해 bash(1)에 의해 실행된다.
# /usr/share/doc/bash/examples/startup-files를 보아라.(bash-doc 패키지 안에 있는)
# 예를 들어

# 만약 상호작용적으로 실행되지 않는 다면, 아무것도 하지 마라.
case $- in
    *i*) ;;
      *) return;;
esac

# 히스토리 안에 중복된 라인들이나 빈 공간으로 시작하는 라인들을 넣지 마라.
# 더 많은 옵션에 대해선 bash(1)을 보아라.
HISTCONTROL=ignoreboth

# 히스토리 파일에 추가해라, 거기에 덮어쓰진 마라.
shopt -s histappend

# 히스토리 길이를 설정하기 위해선 bash(1)에 있는 HISTSIZE와 HISTFILESIZE를 봐라.
HISTSIZE=1000
HISTFILESIZE=2000

# 각각의 명령 후에 윈도우 사이즈를 확인하고 필요하다면
# 행과 열 값을 갱신해라.
shopt -s checkwinsize

# 설정했다면, 패스네임 확장 문맥에 사용된“**”패턴은
# 모든 파일과 0 혹은 더 많은 디렉토리들과 서브 디렉토리들과 일치할 것이다.
#shopt -s globstar

# 비텍스트 입력 파일들에 대해 less를 더 친근하게 만들고, lesspipe(1)를 봐라.
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# 작업하고 있는 chroot를 식별하는 변수를 설정해라. (프롬프트 하에 사용되는)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# 화려한 프롬프트를 설정해라. (색깔을 “원한다”를 알고 있지 않다면, 색은 없음)
case "$TERM" in
    xterm-color) color_prompt=yes;;
esac

# 터미널이 가능하다면 색이 있는 프롬프트에 대해 주석을 해제한다.;
# 사용자를 혼란스럽게 하지 않기 위해 디폴트 값을 해제해라 : 터미널 창에서 초점은
# 프롬프트에가 아닌 명령의 결과물에 있어야 된다.
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# 우리는 색상 지원이 있다; Ecma-48과 부합하다고 가정해 보자.
	# (ISO/IEC-6429). (그러한 지원의 부족은 극히 드물고, 그러한
	# 경우는 setaf보다 setf를 지원하는 경향이 있다.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# 만약 xterm일 경우, 제목을 user@host:dir로 설정해라.
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# ls의 색까라 지원을 할 수 있게 하고 간단한 명령어를 추가해라.
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# some more ls aliases
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

# 오랫동안 실행하는 명령들을 위해 "alert" 명령어를 추가해라. 다음과 같이 :
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# 명령어 정의들.
# ~/.bash_aliases와 같은 분리된 파일에 추가한 사항들을 넣길 원할지도 모른다.
# 여기에 직접 그 사항들을 추가하는 대신에.
# bash-doc 패키지에 있는 /usr/share/doc/bash-doc/examples를 봐라.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# 사용가능하며 프로그래밍할 수 있는 마지막 특징 (이미 /etc/bash.bashrc와 /etc/profile
# sources /etc/bash.bashrc에서 사용할 수 있다면 이것을 사용하게할 필요는 없다.)
# sources /etc/bash.bashrc).
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi
