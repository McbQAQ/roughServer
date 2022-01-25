# roughServer

version 0.01:
    description: only support GET method.
    bug: HttpRequest::write() deal boundary condition badly, "if (writeBufIdx >= sendData[0].iov_len + sendData[1].iov_len)" trap in dead loop due to uninitialized sendData[1];
         When request queue is full, the requests that are unable to add cannot be added again.

version 0.02:
    description: same function with 0.01.
    bug:
    fix: repair bugs in version 0.01.
