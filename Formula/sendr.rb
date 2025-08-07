class Sendr < Formula
  desc "A CLI tool to search Anna's Archive, download books, and have them automatically e-mailed to a Kindle"
  homepage "https://github.com/drustill/sendr"
  url "https://github.com/drustill/sendr/releases/download/v0.1.0/sendr.macos.tar.gz"
  sha256 "5192c10eeb0a3c9e7d37b5f8a11676bc230fb42f4f6b0fcaed992da1a453a36f"
  version "0.1.0"

  def install
    bin.install "sendr"
  end
end
