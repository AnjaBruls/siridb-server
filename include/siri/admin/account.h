/*
 * account.h - SiriDB Administrative User.
 *
 * author       : Jeroen van der Heijden
 * email        : jeroen@transceptor.technology
 * copyright    : 2017, Transceptor Technology
 *
 * changes
 *  - initial version, 16-03-2017
 *
 */
#pragma once
#include <qpack/qpack.h>
#include <siri/siri.h>

typedef struct siri_s siri_t;

typedef struct siri_admin_account_s
{
    char * account;
    char * password; /* keeps an encrypted password */
} siri_admin_account_t;

int siri_admin_account_init(siri_t * siri);
void siri_admin_account_destroy(siri_t * siri);
int siri_admin_account_new(
        siri_t * siri,
        qp_obj_t * qp_account,
        qp_obj_t * qp_password,
        int is_encrypted,
        char * err_msg);
int siri_admin_account_check(
        siri_t * siri,
        qp_obj_t * qp_account,
        qp_obj_t * qp_password,
        char * err_msg);
int siri_admin_account_change_password(
        siri_t * siri,
        qp_obj_t * qp_account,
        qp_obj_t * qp_password,
        char * err_msg);
int siri_admin_account_drop(
        siri_t * siri,
        qp_obj_t * qp_account,
        char * err_msg);
int siri_admin_account_save(siri_t * siri, char * err_msg);
