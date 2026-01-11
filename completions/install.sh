#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
COMPLETIONS_DIR="$SCRIPT_DIR"
SHELL_NAME=$(basename "$SHELL")

echo "[sendr] Shell completions for $SHELL_NAME..."

case "$SHELL_NAME" in
    zsh)
        ZSH_COMPLETION_DIR="$HOME/.zsh/completions"
        mkdir -p "$ZSH_COMPLETION_DIR"
        cp "$COMPLETIONS_DIR/sendr.zsh" "$ZSH_COMPLETION_DIR/_sendr"
        echo "[sendr] ✓ Completion installed to $ZSH_COMPLETION_DIR/_sendr"
        
        if ! grep -q "fpath.*\.zsh/completions" "$HOME/.zshrc" 2>/dev/null; then
            echo ""
            echo "[sendr] Add to ~/.zshrc:"
            echo "  fpath=(~/.zsh/completions \$fpath)"
            echo "  autoload -U compinit && compinit"
        fi
        ;;
    *)
        echo "[sendr] Shell $SHELL_NAME not supported"
        exit 1
        ;;
esac

echo "[sendr] Reload shell by running:"
case "$SHELL_NAME" in
    zsh) echo "  source ~/.zshrc" ;;
esac
