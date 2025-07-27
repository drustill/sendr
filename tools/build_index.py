"""
Generate a lightweight serach index from a corpus of .zst metadata files.

Scans all .zst files in `data/` and extracts fields into a `.tsv` file.
No inverted indexing happens here. Really this just makes a simple grep search
fast enough.

`python tools/build_index.py` or `python build_index.py` from within `tools/`
"""

import zstandard as zstd
import json
import pathlib

SCRIPT = pathlib.Path(__file__).resolve().parent
DATA = SCRIPT.parent / "data"

datapath = pathlib.Path(DATA)
output_file = datapath / "index.tsv"

with open(output_file, "w", encoding="utf-8") as out:
    for zst_file in datapath.glob("*.zst"):
        print(f"Indexing {zst_file}...")
        with open(zst_file, "rb") as fh:
            dctx = zstd.ZstdDecompressor()
            with dctx.stream_reader(fh) as reader:
                for line in reader:
                    try:
                        record = json.loads(line)
                        meta = record.get("metadata", {})
                        title = meta.get("title", "").lower()
                        author = meta.get("author", "").lower()
                        lang = meta.get("language", "")
                        md5 = meta.get("md5_reported", "")
                        if title and md5:
                            out.write(f"{title}\t{author}\t{lang}\t{md5}\n")
                    except Exception:
                        continue

print(f"Index in {output_file}")
