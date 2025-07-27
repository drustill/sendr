"""
Generate a lightweight serach index from a corpus of .zst metadata files.

Scans all .zst files in `data/` and extracts fields into a `.tsv` file.
No inverted indexing happens here. Really this just makes a simple grep search
fast enough.

`python tools/build_index.py` or `python build_index.py` from within `tools/`
"""

import io
import json
import pathlib
import sys

import zstandard as zstd

SCRIPT = pathlib.Path(__file__).resolve().parent
DATA = SCRIPT.parent / "data"

datapath = pathlib.Path(DATA)
output_file = datapath / "index.tsv"

count = 0

cctx = zstd.ZstdCompressor(level=10)
with open(output_file, "wb") as raw_out:
    with cctx.stream_writer(raw_out) as out:
        for zst_file in datapath.glob("*.zst"):
            print(f"Indexing {zst_file}...")
            with open(zst_file, "rb") as fh:
                dctx = zstd.ZstdDecompressor()
                with dctx.stream_reader(fh) as reader:
                    text_stream = io.TextIOWrapper(reader, encoding="utf-8")
                    for line in text_stream:
                        try:
                            record = json.loads(line)
                            meta = record.get("metadata", {})
                            title = meta.get("title", "").lower()
                            author = meta.get("author", "").lower()
                            lang = meta.get("language", "")
                            md5 = meta.get("md5_reported", "")
                            if title and md5 and lang == "english":
                                row = f"{title}\t{author}\t{lang}\t{md5}\n"
                                out.write(row.encode("utf-8"))
                                count += 1
                                if count % 100000 == 0:
                                    sys.stdout.write(f"\rIndexed {count:,} entries...")
                                    sys.stdout.flush()
                        except Exception:
                            continue

print(f"Index in {output_file}")
