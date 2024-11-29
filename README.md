
# Multi-dataset Dictionary - Group 2

  

CS163 - Group Project - Group 2

  

## How to run the project (MacOS)

1. Navigate to the project folder.

2. Execute the binary by: bin/main.

  

After this, the project should be running.
## Issue: Items Require Double-Clicking to Respond
If you find that some elements require double-clicking to work instead of a single-click, this seems to be a SFML problem. It is triggered when you (may) have clicked on the icon of the program when it is starting up. The SFML window has lost focus despite some how still able to poll double-click event as two separate single-click event. However, it is unable to regain focus when being clicked on. This happens when auto-save is turned on and the last save (serialized data) is large.
### To get around this
---
Simply switch to another program and switch back to the original SFML window.
