class Sendr < Formula
  desc "A CLI tool to search Anna's Archive, download books, and have them automatically e-mailed to a Kindle"
  homepage "https://github.com/drustill/sendr"
  url "https://github.com/drustill/sendr/releases/download/v0.1.0/sendr.macos.tar.gz"
  sha256 "REPLACE_WITH_REAL_SHA"
  version "0.1.0"

  def install
    bin.install "sendr"
  end
end
