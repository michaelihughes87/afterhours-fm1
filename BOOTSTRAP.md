# Import the SLOOP baseline into AFTERHOURS

The GitHub connector can read this repository but its current integration grant rejects write operations. The included `bootstrap-afterhours.sh` performs the first import locally on your Mac using your own GitHub credentials.

It will:
1. Clone the public SLOOP source, preserving its full Git history.
2. Rename the SLOOP remote to `upstream`.
3. Add `michaelihughes87/afterhours-fm1` as `origin`.
4. Preserve the upstream README as `SLOOP_README.md`.
5. Add the latest AFTERHOURS product specification and design documents.
6. Commit and push the `main` branch to your empty GitHub repository.

## Before running

- Install Apple's Command Line Tools (the installer you started includes Git).
- Configure Git's author identity (`git config --global user.name` and `git config --global user.email`).
- Authenticate Git push access to GitHub. GitHub CLI (`gh`) is optional; you can use the macOS Keychain / Git Credential Manager or a GitHub CLI login.
- Confirm `https://github.com/michaelihughes87/afterhours-fm1` is still empty.
- Extract this ZIP package.

## Run

From Terminal, change to the extracted folder and run:

```sh
chmod +x bootstrap-afterhours.sh
./bootstrap-afterhours.sh
```

Optional destination folder:

```sh
./bootstrap-afterhours.sh "$HOME/Developer/afterhours-fm1"
```

The script stops if the destination already exists and is non-empty. It does not flash firmware or change the FM-1.

After the push, visit the GitHub repository and confirm the source files and docs are present. The next step is a clean upstream build and regression test on the Mac.
