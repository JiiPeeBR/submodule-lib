#!/usr/bin/env python3
"""Name-only obsolete library finder.

Loads `obsoleteLibs.json` and checks keys (library names) against file and
directory names under `Logical/Libraries`. Case-insensitive name matching only.
Writes a text report (default `obsolete_matches_report.txt`).
"""

from pathlib import Path
import json
import argparse
import sys


def load_lib_names(path: Path):
    with path.open("r", encoding="utf-8") as f:
        data = json.load(f)
    return {k.lower(): (k, v) for k, v in data.items()}


def find_name_matches(libs_dir: Path, lib_map: dict):
    matches = []
    if not libs_dir.exists():
        return matches

    for entry in libs_dir.iterdir():
        if not entry.is_dir():
            continue
        key = entry.name.lower()
        if key in lib_map:
            orig, reason = lib_map[key]
            matches.append({"name": orig, "reason": reason, "path": str(entry)})

    return matches


def write_report(matches, out_path: Path):
    with out_path.open("w", encoding="utf-8") as f:
        if not matches:
            f.write("No obsolete library matches found.\n")
            return
        for m in matches:
            f.write(f"{m['name']} -> {m['path']}\n")
            f.write(f"  Reason: {m['reason']}\n\n")


def main(argv=None):
    print("Running prebuild script to look for obsolete libraries")
    p = argparse.ArgumentParser(description="Name-only obsolete library checker")
    p.add_argument("--root", help="Workspace root (defaults to script parent)", default=None)
    p.add_argument("--out", help="Report output path (defaults to script folder)", default=None)
    args = p.parse_args(argv)

    script_dir = Path(__file__).resolve().parent

    # obsoleteLibs.json is located next to the script per user contract
    obsolete_json = script_dir / "obsoleteLibs.json"
    if not obsolete_json.exists():
        print(f"Could not find obsoleteLibs.json at {obsolete_json}")
        return 2

    lib_map = load_lib_names(obsolete_json)

    # Determine libs_dir:
    # - If --root provided, use <root>/Logical/Libraries
    # - Otherwise compute workspace root from script location: script_dir is
    #   <workspace>/Logical/Scripts so workspace_root = script_dir.parent.parent
    if args.root:
        libs_dir = Path(args.root) / "Logical" / "Libraries"
    else:
        workspace_root = script_dir.parent.parent
        libs_dir = workspace_root / "Logical" / "Libraries"
    
    matches = find_name_matches(libs_dir, lib_map)

    out_path = Path(args.out) if args.out else (script_dir / "obsolete_matches_report.txt")
    write_report(matches, out_path)

    if not matches:
        print("No obsolete library matches found.")
        return 0

    # If we found any obsolete libraries, report error and exit with code 1
    print("Error: obsolete libraries found")
    sys.exit(1)


if __name__ == "__main__":
    sys.exit(main())
