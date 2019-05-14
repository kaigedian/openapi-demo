#include "RSATool.hpp"
#include <iostream>
#include <string>

#define SHA256RSA_PRIVATEKEY        "MIICXQIBAAKBgQDP8fP04cd+BnSC9i3BV4O3UCStJdlglE0T/o+ucVTWz3aveuKc9x6L4jGV1FvM+qEMbqp3DDpvzNlX6OGUf2T7z1QthcUTZzg6fZUehTQ9NVbBWqVaWu4vJ62l2swM0iBMOWph5d60PiafH1aA2//yQjY4LFC+rxh/31eoh2t1pwIDAQABAoGBAKAWb2/5WfHF2nDwQW11iGvaAUJjvyRBR826zrbHfT8a3Q5flpKtFREwBGiK4lm+IbpGgGnCOkLT/AdXvELsiLqHhQZ2qnYfDEaw//N73oBRS6ExW3/UBj7vEb/0HJz+rd/fxDzwsa3co3b7eCtLYqz0BuCt2bCuaOYY47MGIoTxAkEA9XrnQqZildA7GNWfotdv+ffoffQt5GhwGg6g8UWXtGeKZ9bR0jCj4d43MnRpT6gHb8QFpktKRI2jRLtC/QYI+wJBANjbQ3aDm23FxnpW45pFrxVq83b6Ak0RbTwItDT98WFVHMvICz8w2L+k2D9Jv5vw2poqu4lESZ9F1/UR6MYG/kUCQGLG8LWWBAdqgc0tcI3zCKDaC5hbH/hPugQSLNrI+RFjtIKyIz3jyp4Bb86CnzmpUEy94NQYaasKH09x1rO/sO8CQElYb8rn3GwWVnkOZlDJfNxLnikBikGywTVq5DiAI2H+PY0XDebDiKvY/2L4eJwvrGA0T9WviQ8bul0jP42q09kCQQCOJ8pWqlfiqSMdG1+zt2vPHkc+Kt9pqe7nx/s8YzyKVYkWgQ+VdOBmP+rDXIY6klvUkLFRTVS3f5ix+SWv9Zrx"
#define SHA256RSA_PUBLICEKEY        "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDP8fP04cd+BnSC9i3BV4O3UCStJdlglE0T/o+ucVTWz3aveuKc9x6L4jGV1FvM+qEMbqp3DDpvzNlX6OGUf2T7z1QthcUTZzg6fZUehTQ9NVbBWqVaWu4vJ62l2swM0iBMOWph5d60PiafH1aA2//yQjY4LFC+rxh/31eoh2t1pwIDAQAB"

using std::cout;
using std::endl;
using std::string;

int main()
{
    string in("123456789abcdefg123456789abcdefg123456789abcdefg");
    char out[1024] = {0};

    if(RSATool::RSASign(in.c_str(), out, 1024, SHA256RSA_PRIVATEKEY) == 0)
    {
        cout << "RSATool::RSASign ERROR" << endl;
        return 1;
    }

    cout << "RSA sign (base64) : " << out << endl;

    string sign = "ZJn9c4IiphWeqiL/dzhxuZAH4zSnB+RNMMnSCiU9kKikJzmSTF1cUS3SHmgVqRtftmUA/whzIJbJDdlDYgCRBJyo51QbXtGmA2yqRv89dC9LL+XFVjFv4hMwlYoOGc2hrkvWpRTrGsrSC/upLst/lb3MiqugKzgRFIGg3/3n4Ls=";

    if(RSATool::RSAVerify(in.c_str(), sign.c_str(), SHA256RSA_PUBLICEKEY) == 0)
    {
        cout << "RSATool::RSASign ERROR" << endl;
        return 1;
    }

    cout << "RSATool::RSASign SUCCESS" << endl;

    return 0;
}
