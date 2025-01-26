#!/bin/bash

diff <(gr 1) <(cat <<EOS
... # Expected output
EOS
)
