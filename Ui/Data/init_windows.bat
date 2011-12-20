SET SOURCE_PATH=%1
SET TARGET_PATH=%2
echo "Source path: %SOURCE_PATH%"
echo "Target path: %TARGET_PATH%"
echo "Copy Checkpoints_positions.pos to target path"
copy %SOURCE_PATH%\Checkpoints_positions.pos %TARGET_PATH%\Checkpoints_positions.pos

