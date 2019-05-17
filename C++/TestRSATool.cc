#include "RSATool.hpp"
#include "URLCode.hpp"
#include <iostream>
#include <string>

#define SHA256RSA_PRIVATEKEY        "MIIEowIBAAKCAQEAvvpi831l5fBOe/k2eHi2yu6DlDKf6PROdMBHkKp0vlotS9f/crqr2Q7NEqpxi5/MrnjzKcPhipREfhdR74oEYpC2Wgi0S9oLiXBOPiwnmijyhYEzuDVwFFDTtHV54p3nAX3MkVEhaGSmqPq+ddxyRscYLBBJp1K2zkyJ6yQUeDH6paJMchyIkTHwyMCimsg2VJbs1MO+nZsLA8Rlp3Y5Ublk7LGniFxCgQruwTwziSP4/yG0yYoU4Vsa5sH+/mj8wKZNuKYKnWcw9dAR8JvDkKQXIFa7ZdkWToszr2PnIZB80Hgztmu3LJkYecfCs60tNVSce2zWTjylQYQuBLDNfwIDAQABAoIBAHtQV8ZbSQmRAkyAnZBqebVNDz8I9UJJRcOTSGJ7/gfPWIIphXNCX6Y3LWmJDuoWE+bwiCqGpcKCfDtiuXBPkQdH48b86dY0g9CJ6KuyfRvIpthXldqy/pzPl/NlC3+tb7UB0q5eUZEDtK1Vwtd9sXhMJCqHlddpzEonF8LyOBlnJhGpOrJ6UUKlHU0GtLW9RKpAxIj22mWKH2Fl6gF5CUhLJC5pkkHo6NHVHPLejUoMQyCPMUjtAkP6qsihm0lJMN5oJr9pL88favqV+Q3f8eWpRVrfBfz2IjGKzk9lS5DKpnJuixt0+8aw6iBliyjWA9MExOCAG4LdNbF9841K92kCgYEA63TagxKlTuR+/c+z/ajvqNovd/53t6uyo2scczHZg8+dSPDofsUcFyfrRwD0oaRMT+wzc8DqjbMkrZmvOWy/C0aI9XrpFX6HLrT/G3qzDuzTqDa9Ih7iSTKAiJ9+GN+vegerAC9SSe7f6+SE98Ya7Ay9H7xWF67MsTc3BPDpI2UCgYEAz6QQv5evMpQkOlCOdrw/LNz8RXC1yisjxpVpZFvJRxn4RMv0CNq0MJUkVTqZWN3xTCjYq4q2JXGQHpN7ZMbCEvhL7nqiMV3RzDfkt39bw5EMIWFX0pEZ1VhQSaNzA+LmNko9B9BAEey4qsZ+jyTPF1TiF2DJwfNDD+HYDvpYKRMCgYA1OBNPvv4oR9NAURsQwYdx9eb2y0iJ9kAJWeNzUhglB984JmOWi7zeqwIt6VRh2L367ptulXMulgg7SNpnM2I3DTlVqvNWDWRGtVhYALLKM9NfWQgE11A0VTriJpKc0qpZ/bOz9f42gcyRB/TaACgDpJl2u94Fule/0ogYEM/RVQKBgFO0DLhfelXGWFBVtwhwXHtGXj/T7sSf3V0pUAIP6jTKaEW7fhWvrGHFTY85/yVO2v3bnXSRh1nSzMk2pNB8OzIQe/OX5hhGfNN5WK8MHT7aEuzF4/RTX/mcD0mQJUZUyn7qMG4c6icPqWXWfKBRs1Xxdu77qnmQCeG2JjXrf2yXAoGBAMw3wLfMA989qi8Q0uhI9JCNibZYrFqgVwxTVzwaRyd/9KyXDLrDf1RiYkJg4zU+4t3vwtnjvbmpPelQW/EYewpFSmfmT7G82SroYRHyCDnl2R/x0MJYriwEIfSIF378WqJp9NjZKAhjbwx+1ED5i1tVbsQm5ozNmwhKMO3n8KFu"
#define SHA256RSA_PUBLICEKEY        "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAvvpi831l5fBOe/k2eHi2yu6DlDKf6PROdMBHkKp0vlotS9f/crqr2Q7NEqpxi5/MrnjzKcPhipREfhdR74oEYpC2Wgi0S9oLiXBOPiwnmijyhYEzuDVwFFDTtHV54p3nAX3MkVEhaGSmqPq+ddxyRscYLBBJp1K2zkyJ6yQUeDH6paJMchyIkTHwyMCimsg2VJbs1MO+nZsLA8Rlp3Y5Ublk7LGniFxCgQruwTwziSP4/yG0yYoU4Vsa5sH+/mj8wKZNuKYKnWcw9dAR8JvDkKQXIFa7ZdkWToszr2PnIZB80Hgztmu3LJkYecfCs60tNVSce2zWTjylQYQuBLDNfwIDAQAB"
using std::cout;
using std::endl;
using std::string;

int main()
{
    string in("appId=wxaa246&partnerId=2282&requestBody={\"orderCode\":[\"14466581149538022700014\"]}&ver=1");
    char out[25600] = {0};

    if(RSATool::RSASign(in.c_str(), out, 25600, SHA256RSA_PRIVATEKEY) == 0)
    {
        cout << "RSATool::RSASign ERRORS" << endl;
        return 1;
    }

    cout << "RSA sign (base64) : " << out << endl;

    string sign = "c33TwZkf4drwaYusivkDil1go8sekvKqQL8+pxBfPy4Yw9Hdh3VjPhgQQOxVaiSmHLuM8YWBudzYmRX4buybVggQ+Y5C6rHZu0boWlVZNdQ/AaeZVZ1hVLHfSh5xkU20Q7ABh/oMdycYK2IE9tGDZVptdD8twdy1KO9vbb0bky39JDw2aRJUW23ILHmCiGquLzF6hQMDFxVihj2Zl6OdDzhZzHA3ng7d0He9bGxnHR3Z2Wi/gf6hlocy9Kn1soIrzbHjW+rGUf8mzbhrrDOubM/qZ5wlK7p5+lfL66XF5bPFMvuUMrqUfH6zN2JA7LwKyljFPfcO5MZy1k0d2lbo3Q==";

    if(RSATool::RSAVerify(in.c_str(), sign.c_str(), SHA256RSA_PUBLICEKEY) == 0)
    {
        cout << "RSATool::RSASign ERROR" << endl;
        return 1;
    }

    cout << "RSATool::RSASign SUCCESS" << endl;

    std::string str("{\"startTimestamp\":1558000669,\"endTimestamp\":1558000679,\"orderClients\":[1],\"storeId\":\"1234\",\"orderStatus\":[1,3,31,4,5,6,7],\"pageNum\":1,\"pageSize\":10}");

    std::string outs = URLTool::UrlEncode(str);

    cout << outs.data() << endl;

    return 0;
}
