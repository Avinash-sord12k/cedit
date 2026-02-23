#!/bin/bash
set -e

INSTALL_PATH="/usr/local/bin/cedit"

# uninstall
if [ "$1" = "uninstall" ]; then
  if [ -f "$INSTALL_PATH" ]; then
    sudo rm "$INSTALL_PATH"
    echo "cedit removed."
  else
    echo "cedit is not installed."
  fi
  exit 0
fi

REPO="Avinash-sord12k/cedit"

ARCH=$(uname -m)
OS=$(uname -s)

if [ "$OS" != "Linux" ]; then
  echo "Unsupported OS: $OS"
  echo "Please build from source:"
  echo "https://github.com/$REPO"
  exit 1
fi

case "$ARCH" in
  x86_64|amd64)
    PLATFORM="linux-x86_64"
    ;;
  aarch64|arm64)
    PLATFORM="linux-arm64"
    ;;
  *)
    echo "Unsupported architecture: $ARCH"
    echo "Please build from source:"
    echo "https://github.com/$REPO"
    exit 1
    ;;
esac

# fetch latest release tag
LATEST=$(curl -fsSL https://api.github.com/repos/$REPO/releases \
  | grep -m 1 '"tag_name"' \
  | cut -d '"' -f4)

if [ -z "$LATEST" ]; then
  echo "Could not determine latest release."
  exit 1
fi

echo "Found latest cedit release: $LATEST"

# detect installed version (if exists)
if command -v cedit >/dev/null 2>&1; then
  INSTALLED_VERSION=$(cedit --version 2>/dev/null | grep -oE 'v[0-9]+\.[0-9]+\.[0-9]+')
  echo "Found installed cedit version: $INSTALLED_VERSION"
else
  INSTALLED_VERSION=""
fi

if [ "$INSTALLED_VERSION" = "$LATEST" ]; then
  echo "cedit is already up to date ($LATEST)"
  exit 0
fi

if [ -n "$INSTALLED_VERSION" ]; then
  echo "Upgrading cedit from $INSTALLED_VERSION to $LATEST"
else
  echo "Installing cedit $LATEST"
fi

BIN_NAME="cedit-${LATEST}-${PLATFORM}"
URL="https://github.com/$REPO/releases/download/${LATEST}/${BIN_NAME}"
echo "URL: $URL"

echo "Downloading $BIN_NAME ..."

curl -fL "$URL" -o cedit || {
  echo "Binary not available for $PLATFORM."
  echo "Please build from source:"
  echo "https://github.com/$REPO"
  exit 1
}

chmod +x cedit
sudo mv cedit $INSTALL_PATH

echo "Installed cedit ($LATEST)"
echo "Run with: cedit file.txt"