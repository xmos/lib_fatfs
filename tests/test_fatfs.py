# Copyright 2026 XMOS LIMITED.
# This Software is subject to the terms of the XMOS Public Licence: Version 1.
from pathlib import Path
import subprocess
import pytest

test_path = Path(__file__).parent


@pytest.mark.parametrize("binary", sorted(test_path.glob("*/bin/*.xe")), ids=lambda b: b.stem)
def test_fatfs(binary):
    result = subprocess.run(["xsim", str(binary)], capture_output=True, text=True, timeout=600)
    assert result.returncode == 0, result.stdout + result.stderr
    assert result.stdout.splitlines()[-1].startswith("PASS:"), result.stdout + result.stderr
