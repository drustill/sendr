#compdef sendr
_sendr() {
    if (( CURRENT == 2 )); then
        local -a commands
        commands=(
            'search:Search for books'
            'daemon:Manage the daemon process'
        )
        _describe 'command' commands
    elif [[ $words[2] == search ]]; then
        _arguments \
            '--max[Limit to top N matches]:number:' \
            '--format[Desired format]:format:(epub pdf mobi azw3)' \
            '--dry-run[Print download URL, don'\''t download or send]' \
            '--query[Search query in quotes]:query:'
    elif [[ $words[2] == daemon ]]; then
        if (( CURRENT == 3 )); then
            local -a daemon_commands
            daemon_commands=(
                'start:Launch the daemon process'
                'stop:Stop the running daemon'
                'restart:Restart the daemon'
                'status:Print daemon status'
            )
            _describe 'daemon command' daemon_commands
        fi
    fi
}

_sendr "$@"
