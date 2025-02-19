#ifndef TOKI_H
#define TOKI_H

#include "base64.h"
#include "hmac.h"
#include "sha.h"
#include "hashmap.h"
#include "jacon.h"
#include "jutils.h"
#include "server.h"

typedef enum {
    TOKI_OK,
    TOKI_INVALID_TOKEN,
    TOKI_ERR_NULL_PARAM,
    TOKI_ERR_ADD_CLAIM,
    TOKI_ERR_UNSUPPORTED_ALGORITHM,
} Toki_Error;

typedef enum {
    TOKI_ALG_HS256,
    TOKI_ALG_HS384,
    TOKI_ALG_HS512,
} Toki_Alg;

typedef Jacon_Node Toki_Claims;
typedef Jacon_Node Toki_Payload;

typedef struct Toki_Token {
    Toki_Claims header;
    Toki_Payload payload;
    Toki_Alg algorithm;
} Toki_Token;

/**
 * Initializes a token with the provided algorithm
 * Sets the token's header to
 *      {
 *          "alg": "provided_alg",
 *          "typ": "JWT"
 *      }
 */
Toki_Error
Toki_token_init(Toki_Token* token, Toki_Alg algorithm);

Toki_Error
Toki_add_claim(Toki_Token* token, Jacon_Node* claim);

/**
 * Signs a token and sets signed_token to the signed token value
 */
Toki_Error
Toki_sign_token(Toki_Token* token, const char* key, char** signed_token);

/**
 * Verify a token
 * Based on token signature and optionnal registered claims
 *  (iss, sub, aud, exp, nbf, iat, jti)
 */
bool
Toki_verify_token(const char* token);

/**
 * Free allocated ressources
 */
void
Toki_free_token(Toki_Token* token);

void
Toki_setup_env(Ws_Config* config);

#endif // TOKI_H