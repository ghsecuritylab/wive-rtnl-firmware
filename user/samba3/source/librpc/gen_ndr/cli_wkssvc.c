/*
 * Unix SMB/CIFS implementation.
 * client auto-generated by pidl. DO NOT MODIFY!
 */

#include "includes.h"
#include "librpc/gen_ndr/cli_wkssvc.h"

NTSTATUS rpccli_wkssvc_NetWkstaGetInfo(struct rpc_pipe_client *cli,
				       TALLOC_CTX *mem_ctx,
				       const char *server_name /* [in] [unique,charset(UTF16)] */,
				       uint32_t level /* [in]  */,
				       union wkssvc_NetWkstaInfo *info /* [out] [ref,switch_is(level)] */,
				       WERROR *werror)
{
	struct wkssvc_NetWkstaGetInfo r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.level = level;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetWkstaGetInfo, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETWKSTAGETINFO,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetWkstaGetInfo, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*info = *r.out.info;

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetWkstaSetInfo(struct rpc_pipe_client *cli,
				       TALLOC_CTX *mem_ctx,
				       const char *server_name /* [in] [unique,charset(UTF16)] */,
				       uint32_t level /* [in]  */,
				       union wkssvc_NetWkstaInfo *info /* [in] [ref,switch_is(level)] */,
				       uint32_t *parm_error /* [in,out] [ref] */,
				       WERROR *werror)
{
	struct wkssvc_NetWkstaSetInfo r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.level = level;
	r.in.info = info;
	r.in.parm_error = parm_error;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetWkstaSetInfo, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETWKSTASETINFO,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetWkstaSetInfo, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*parm_error = *r.out.parm_error;

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetWkstaEnumUsers(struct rpc_pipe_client *cli,
					 TALLOC_CTX *mem_ctx,
					 const char *server_name /* [in] [unique,charset(UTF16)] */,
					 struct wkssvc_NetWkstaEnumUsersInfo *info /* [in,out] [ref] */,
					 uint32_t prefmaxlen /* [in]  */,
					 uint32_t *entries_read /* [out] [ref] */,
					 uint32_t *resume_handle /* [in,out] [unique] */,
					 WERROR *werror)
{
	struct wkssvc_NetWkstaEnumUsers r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.info = info;
	r.in.prefmaxlen = prefmaxlen;
	r.in.resume_handle = resume_handle;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetWkstaEnumUsers, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETWKSTAENUMUSERS,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetWkstaEnumUsers, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*info = *r.out.info;
	*entries_read = *r.out.entries_read;
	if (resume_handle && r.out.resume_handle) {
		*resume_handle = *r.out.resume_handle;
	}

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrWkstaUserGetInfo(struct rpc_pipe_client *cli,
					    TALLOC_CTX *mem_ctx,
					    const char *unknown /* [in] [unique,charset(UTF16)] */,
					    uint32_t level /* [in]  */,
					    union wkssvc_NetrWkstaUserInfo *info /* [out] [ref,switch_is(level)] */,
					    WERROR *werror)
{
	struct wkssvc_NetrWkstaUserGetInfo r;
	NTSTATUS status;

	/* In parameters */
	r.in.unknown = unknown;
	r.in.level = level;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrWkstaUserGetInfo, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRWKSTAUSERGETINFO,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrWkstaUserGetInfo, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*info = *r.out.info;

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrWkstaUserSetInfo(struct rpc_pipe_client *cli,
					    TALLOC_CTX *mem_ctx,
					    const char *unknown /* [in] [unique,charset(UTF16)] */,
					    uint32_t level /* [in]  */,
					    union wkssvc_NetrWkstaUserInfo *info /* [in] [ref,switch_is(level)] */,
					    uint32_t *parm_err /* [in,out] [unique] */,
					    WERROR *werror)
{
	struct wkssvc_NetrWkstaUserSetInfo r;
	NTSTATUS status;

	/* In parameters */
	r.in.unknown = unknown;
	r.in.level = level;
	r.in.info = info;
	r.in.parm_err = parm_err;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrWkstaUserSetInfo, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRWKSTAUSERSETINFO,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrWkstaUserSetInfo, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	if (parm_err && r.out.parm_err) {
		*parm_err = *r.out.parm_err;
	}

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetWkstaTransportEnum(struct rpc_pipe_client *cli,
					     TALLOC_CTX *mem_ctx,
					     const char *server_name /* [in] [unique,charset(UTF16)] */,
					     struct wkssvc_NetWkstaTransportInfo *info /* [in,out] [ref] */,
					     uint32_t max_buffer /* [in]  */,
					     uint32_t *total_entries /* [out] [ref] */,
					     uint32_t *resume_handle /* [in,out] [unique] */,
					     WERROR *werror)
{
	struct wkssvc_NetWkstaTransportEnum r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.info = info;
	r.in.max_buffer = max_buffer;
	r.in.resume_handle = resume_handle;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetWkstaTransportEnum, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETWKSTATRANSPORTENUM,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetWkstaTransportEnum, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*info = *r.out.info;
	*total_entries = *r.out.total_entries;
	if (resume_handle && r.out.resume_handle) {
		*resume_handle = *r.out.resume_handle;
	}

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrWkstaTransportAdd(struct rpc_pipe_client *cli,
					     TALLOC_CTX *mem_ctx,
					     const char *server_name /* [in] [unique,charset(UTF16)] */,
					     uint32_t level /* [in]  */,
					     struct wkssvc_NetWkstaTransportInfo0 *info0 /* [in] [ref] */,
					     uint32_t *parm_err /* [in,out] [unique] */,
					     WERROR *werror)
{
	struct wkssvc_NetrWkstaTransportAdd r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.level = level;
	r.in.info0 = info0;
	r.in.parm_err = parm_err;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrWkstaTransportAdd, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRWKSTATRANSPORTADD,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrWkstaTransportAdd, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	if (parm_err && r.out.parm_err) {
		*parm_err = *r.out.parm_err;
	}

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrWkstaTransportDel(struct rpc_pipe_client *cli,
					     TALLOC_CTX *mem_ctx,
					     const char *server_name /* [in] [unique,charset(UTF16)] */,
					     const char *transport_name /* [in] [unique,charset(UTF16)] */,
					     uint32_t unknown3 /* [in]  */,
					     WERROR *werror)
{
	struct wkssvc_NetrWkstaTransportDel r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.transport_name = transport_name;
	r.in.unknown3 = unknown3;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrWkstaTransportDel, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRWKSTATRANSPORTDEL,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrWkstaTransportDel, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrUseAdd(struct rpc_pipe_client *cli,
				  TALLOC_CTX *mem_ctx,
				  const char *server_name /* [in] [unique,charset(UTF16)] */,
				  uint32_t level /* [in]  */,
				  union wkssvc_NetrUseGetInfoCtr *ctr /* [in] [ref,switch_is(level)] */,
				  uint32_t *parm_err /* [in,out] [unique] */,
				  WERROR *werror)
{
	struct wkssvc_NetrUseAdd r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.level = level;
	r.in.ctr = ctr;
	r.in.parm_err = parm_err;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrUseAdd, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRUSEADD,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrUseAdd, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	if (parm_err && r.out.parm_err) {
		*parm_err = *r.out.parm_err;
	}

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrUseGetInfo(struct rpc_pipe_client *cli,
				      TALLOC_CTX *mem_ctx,
				      const char *server_name /* [in] [unique,charset(UTF16)] */,
				      const char *use_name /* [in] [ref,charset(UTF16)] */,
				      uint32_t level /* [in]  */,
				      union wkssvc_NetrUseGetInfoCtr *ctr /* [out] [ref,switch_is(level)] */,
				      WERROR *werror)
{
	struct wkssvc_NetrUseGetInfo r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.use_name = use_name;
	r.in.level = level;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrUseGetInfo, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRUSEGETINFO,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrUseGetInfo, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*ctr = *r.out.ctr;

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrUseDel(struct rpc_pipe_client *cli,
				  TALLOC_CTX *mem_ctx,
				  const char *server_name /* [in] [unique,charset(UTF16)] */,
				  const char *use_name /* [in] [ref,charset(UTF16)] */,
				  uint32_t force_cond /* [in]  */,
				  WERROR *werror)
{
	struct wkssvc_NetrUseDel r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.use_name = use_name;
	r.in.force_cond = force_cond;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrUseDel, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRUSEDEL,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrUseDel, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrUseEnum(struct rpc_pipe_client *cli,
				   TALLOC_CTX *mem_ctx,
				   const char *server_name /* [in] [unique,charset(UTF16)] */,
				   struct wkssvc_NetrUseEnumInfo *info /* [in,out] [ref] */,
				   uint32_t prefmaxlen /* [in]  */,
				   uint32_t *entries_read /* [out] [ref] */,
				   uint32_t *resume_handle /* [in,out] [unique] */,
				   WERROR *werror)
{
	struct wkssvc_NetrUseEnum r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.info = info;
	r.in.prefmaxlen = prefmaxlen;
	r.in.resume_handle = resume_handle;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrUseEnum, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRUSEENUM,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrUseEnum, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*info = *r.out.info;
	*entries_read = *r.out.entries_read;
	if (resume_handle && r.out.resume_handle) {
		*resume_handle = *r.out.resume_handle;
	}

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrMessageBufferSend(struct rpc_pipe_client *cli,
					     TALLOC_CTX *mem_ctx,
					     const char *server_name /* [in] [unique,charset(UTF16)] */,
					     const char *message_name /* [in] [ref,charset(UTF16)] */,
					     const char *message_sender_name /* [in] [unique,charset(UTF16)] */,
					     uint8_t *message_buffer /* [in] [ref,size_is(message_size)] */,
					     uint32_t message_size /* [in]  */,
					     WERROR *werror)
{
	struct wkssvc_NetrMessageBufferSend r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.message_name = message_name;
	r.in.message_sender_name = message_sender_name;
	r.in.message_buffer = message_buffer;
	r.in.message_size = message_size;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrMessageBufferSend, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRMESSAGEBUFFERSEND,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrMessageBufferSend, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrWorkstationStatisticsGet(struct rpc_pipe_client *cli,
						    TALLOC_CTX *mem_ctx,
						    const char *server_name /* [in] [unique,charset(UTF16)] */,
						    const char *unknown2 /* [in] [unique,charset(UTF16)] */,
						    uint32_t unknown3 /* [in]  */,
						    uint32_t unknown4 /* [in]  */,
						    struct wkssvc_NetrWorkstationStatistics **info /* [out] [ref] */,
						    WERROR *werror)
{
	struct wkssvc_NetrWorkstationStatisticsGet r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.unknown2 = unknown2;
	r.in.unknown3 = unknown3;
	r.in.unknown4 = unknown4;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrWorkstationStatisticsGet, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRWORKSTATIONSTATISTICSGET,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrWorkstationStatisticsGet, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*info = *r.out.info;

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrLogonDomainNameAdd(struct rpc_pipe_client *cli,
					      TALLOC_CTX *mem_ctx,
					      const char *domain_name /* [in] [ref,charset(UTF16)] */,
					      WERROR *werror)
{
	struct wkssvc_NetrLogonDomainNameAdd r;
	NTSTATUS status;

	/* In parameters */
	r.in.domain_name = domain_name;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrLogonDomainNameAdd, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRLOGONDOMAINNAMEADD,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrLogonDomainNameAdd, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrLogonDomainNameDel(struct rpc_pipe_client *cli,
					      TALLOC_CTX *mem_ctx,
					      const char *domain_name /* [in] [ref,charset(UTF16)] */,
					      WERROR *werror)
{
	struct wkssvc_NetrLogonDomainNameDel r;
	NTSTATUS status;

	/* In parameters */
	r.in.domain_name = domain_name;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrLogonDomainNameDel, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRLOGONDOMAINNAMEDEL,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrLogonDomainNameDel, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrJoinDomain(struct rpc_pipe_client *cli,
				      TALLOC_CTX *mem_ctx,
				      const char *server_name /* [in] [unique,charset(UTF16)] */,
				      const char *domain_name /* [in] [ref,charset(UTF16)] */,
				      const char *account_ou /* [in] [unique,charset(UTF16)] */,
				      const char *Account /* [in] [unique,charset(UTF16)] */,
				      const char *password /* [in] [unique,charset(UTF16)] */,
				      uint32_t join_flags /* [in]  */,
				      WERROR *werror)
{
	struct wkssvc_NetrJoinDomain r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.domain_name = domain_name;
	r.in.account_ou = account_ou;
	r.in.Account = Account;
	r.in.password = password;
	r.in.join_flags = join_flags;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrJoinDomain, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRJOINDOMAIN,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrJoinDomain, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrUnjoinDomain(struct rpc_pipe_client *cli,
					TALLOC_CTX *mem_ctx,
					const char *server_name /* [in] [unique,charset(UTF16)] */,
					const char *Account /* [in] [unique,charset(UTF16)] */,
					const char *password /* [in] [unique,charset(UTF16)] */,
					uint32_t unjoin_flags /* [in]  */,
					WERROR *werror)
{
	struct wkssvc_NetrUnjoinDomain r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.Account = Account;
	r.in.password = password;
	r.in.unjoin_flags = unjoin_flags;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrUnjoinDomain, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRUNJOINDOMAIN,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrUnjoinDomain, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrRenameMachineInDomain(struct rpc_pipe_client *cli,
						 TALLOC_CTX *mem_ctx,
						 const char *server_name /* [in] [unique,charset(UTF16)] */,
						 const char *NewMachineName /* [in] [unique,charset(UTF16)] */,
						 const char *Account /* [in] [unique,charset(UTF16)] */,
						 const char *password /* [in] [unique,charset(UTF16)] */,
						 uint32_t RenameOptions /* [in]  */,
						 WERROR *werror)
{
	struct wkssvc_NetrRenameMachineInDomain r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.NewMachineName = NewMachineName;
	r.in.Account = Account;
	r.in.password = password;
	r.in.RenameOptions = RenameOptions;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrRenameMachineInDomain, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRRENAMEMACHINEINDOMAIN,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrRenameMachineInDomain, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrValidateName(struct rpc_pipe_client *cli,
					TALLOC_CTX *mem_ctx,
					const char *server_name /* [in] [unique,charset(UTF16)] */,
					const char *name /* [in] [ref,charset(UTF16)] */,
					const char *Account /* [in] [unique,charset(UTF16)] */,
					const char *Password /* [in] [unique,charset(UTF16)] */,
					enum wkssvc_NetValidateNameType name_type /* [in]  */,
					WERROR *werror)
{
	struct wkssvc_NetrValidateName r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.name = name;
	r.in.Account = Account;
	r.in.Password = Password;
	r.in.name_type = name_type;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrValidateName, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRVALIDATENAME,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrValidateName, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrGetJoinInformation(struct rpc_pipe_client *cli,
					      TALLOC_CTX *mem_ctx,
					      const char *server_name /* [in] [unique,charset(UTF16)] */,
					      const char **name_buffer /* [in,out] [ref,charset(UTF16)] */,
					      enum wkssvc_NetJoinStatus *name_type /* [out] [ref] */,
					      WERROR *werror)
{
	struct wkssvc_NetrGetJoinInformation r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.name_buffer = name_buffer;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrGetJoinInformation, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRGETJOININFORMATION,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrGetJoinInformation, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*name_buffer = *r.out.name_buffer;
	*name_type = *r.out.name_type;

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrGetJoinableOus(struct rpc_pipe_client *cli,
					  TALLOC_CTX *mem_ctx,
					  const char *server_name /* [in] [unique,charset(UTF16)] */,
					  const char *domain_name /* [in] [ref,charset(UTF16)] */,
					  const char *Account /* [in] [unique,charset(UTF16)] */,
					  const char *unknown /* [in] [unique,charset(UTF16)] */,
					  uint32_t *num_ous /* [in,out] [ref] */,
					  const char ***ous /* [out] [ref,charset(UTF16),size_is(,*num_ous)] */,
					  WERROR *werror)
{
	struct wkssvc_NetrGetJoinableOus r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.domain_name = domain_name;
	r.in.Account = Account;
	r.in.unknown = unknown;
	r.in.num_ous = num_ous;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrGetJoinableOus, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRGETJOINABLEOUS,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrGetJoinableOus, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*num_ous = *r.out.num_ous;
	*ous = *r.out.ous;

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrJoinDomain2(struct rpc_pipe_client *cli,
				       TALLOC_CTX *mem_ctx,
				       const char *server_name /* [in] [unique,charset(UTF16)] */,
				       const char *domain_name /* [in] [ref,charset(UTF16)] */,
				       const char *account_ou /* [in] [unique,charset(UTF16)] */,
				       const char *admin_account /* [in] [unique,charset(UTF16)] */,
				       struct wkssvc_PasswordBuffer *encrypted_password /* [in] [unique] */,
				       uint32_t join_flags /* [in]  */,
				       WERROR *werror)
{
	struct wkssvc_NetrJoinDomain2 r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.domain_name = domain_name;
	r.in.account_ou = account_ou;
	r.in.admin_account = admin_account;
	r.in.encrypted_password = encrypted_password;
	r.in.join_flags = join_flags;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrJoinDomain2, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRJOINDOMAIN2,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrJoinDomain2, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrUnjoinDomain2(struct rpc_pipe_client *cli,
					 TALLOC_CTX *mem_ctx,
					 const char *server_name /* [in] [unique,charset(UTF16)] */,
					 const char *account /* [in] [unique,charset(UTF16)] */,
					 struct wkssvc_PasswordBuffer *encrypted_password /* [in] [unique] */,
					 uint32_t unjoin_flags /* [in]  */,
					 WERROR *werror)
{
	struct wkssvc_NetrUnjoinDomain2 r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.account = account;
	r.in.encrypted_password = encrypted_password;
	r.in.unjoin_flags = unjoin_flags;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrUnjoinDomain2, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRUNJOINDOMAIN2,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrUnjoinDomain2, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrRenameMachineInDomain2(struct rpc_pipe_client *cli,
						  TALLOC_CTX *mem_ctx,
						  const char *server_name /* [in] [unique,charset(UTF16)] */,
						  const char *NewMachineName /* [in] [unique,charset(UTF16)] */,
						  const char *Account /* [in] [unique,charset(UTF16)] */,
						  struct wkssvc_PasswordBuffer *EncryptedPassword /* [in] [unique] */,
						  uint32_t RenameOptions /* [in]  */,
						  WERROR *werror)
{
	struct wkssvc_NetrRenameMachineInDomain2 r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.NewMachineName = NewMachineName;
	r.in.Account = Account;
	r.in.EncryptedPassword = EncryptedPassword;
	r.in.RenameOptions = RenameOptions;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrRenameMachineInDomain2, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRRENAMEMACHINEINDOMAIN2,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrRenameMachineInDomain2, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrValidateName2(struct rpc_pipe_client *cli,
					 TALLOC_CTX *mem_ctx,
					 const char *server_name /* [in] [unique,charset(UTF16)] */,
					 const char *name /* [in] [ref,charset(UTF16)] */,
					 const char *Account /* [in] [unique,charset(UTF16)] */,
					 struct wkssvc_PasswordBuffer *EncryptedPassword /* [in] [unique] */,
					 enum wkssvc_NetValidateNameType name_type /* [in]  */,
					 WERROR *werror)
{
	struct wkssvc_NetrValidateName2 r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.name = name;
	r.in.Account = Account;
	r.in.EncryptedPassword = EncryptedPassword;
	r.in.name_type = name_type;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrValidateName2, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRVALIDATENAME2,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrValidateName2, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrGetJoinableOus2(struct rpc_pipe_client *cli,
					   TALLOC_CTX *mem_ctx,
					   const char *server_name /* [in] [unique,charset(UTF16)] */,
					   const char *domain_name /* [in] [ref,charset(UTF16)] */,
					   const char *Account /* [in] [unique,charset(UTF16)] */,
					   struct wkssvc_PasswordBuffer *EncryptedPassword /* [in] [unique] */,
					   uint32_t *num_ous /* [in,out] [ref] */,
					   const char ***ous /* [out] [ref,charset(UTF16),size_is(,*num_ous)] */,
					   WERROR *werror)
{
	struct wkssvc_NetrGetJoinableOus2 r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.domain_name = domain_name;
	r.in.Account = Account;
	r.in.EncryptedPassword = EncryptedPassword;
	r.in.num_ous = num_ous;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrGetJoinableOus2, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRGETJOINABLEOUS2,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrGetJoinableOus2, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*num_ous = *r.out.num_ous;
	*ous = *r.out.ous;

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrAddAlternateComputerName(struct rpc_pipe_client *cli,
						    TALLOC_CTX *mem_ctx,
						    const char *server_name /* [in] [unique,charset(UTF16)] */,
						    const char *NewAlternateMachineName /* [in] [unique,charset(UTF16)] */,
						    const char *Account /* [in] [unique,charset(UTF16)] */,
						    struct wkssvc_PasswordBuffer *EncryptedPassword /* [in] [unique] */,
						    uint32_t Reserved /* [in]  */,
						    WERROR *werror)
{
	struct wkssvc_NetrAddAlternateComputerName r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.NewAlternateMachineName = NewAlternateMachineName;
	r.in.Account = Account;
	r.in.EncryptedPassword = EncryptedPassword;
	r.in.Reserved = Reserved;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrAddAlternateComputerName, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRADDALTERNATECOMPUTERNAME,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrAddAlternateComputerName, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrRemoveAlternateComputerName(struct rpc_pipe_client *cli,
						       TALLOC_CTX *mem_ctx,
						       const char *server_name /* [in] [unique,charset(UTF16)] */,
						       const char *AlternateMachineNameToRemove /* [in] [unique,charset(UTF16)] */,
						       const char *Account /* [in] [unique,charset(UTF16)] */,
						       struct wkssvc_PasswordBuffer *EncryptedPassword /* [in] [unique] */,
						       uint32_t Reserved /* [in]  */,
						       WERROR *werror)
{
	struct wkssvc_NetrRemoveAlternateComputerName r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.AlternateMachineNameToRemove = AlternateMachineNameToRemove;
	r.in.Account = Account;
	r.in.EncryptedPassword = EncryptedPassword;
	r.in.Reserved = Reserved;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrRemoveAlternateComputerName, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRREMOVEALTERNATECOMPUTERNAME,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrRemoveAlternateComputerName, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrSetPrimaryComputername(struct rpc_pipe_client *cli,
						  TALLOC_CTX *mem_ctx,
						  const char *server_name /* [in] [unique,charset(UTF16)] */,
						  const char *primary_name /* [in] [unique,charset(UTF16)] */,
						  const char *Account /* [in] [unique,charset(UTF16)] */,
						  struct wkssvc_PasswordBuffer *EncryptedPassword /* [in] [unique] */,
						  uint32_t Reserved /* [in]  */,
						  WERROR *werror)
{
	struct wkssvc_NetrSetPrimaryComputername r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.primary_name = primary_name;
	r.in.Account = Account;
	r.in.EncryptedPassword = EncryptedPassword;
	r.in.Reserved = Reserved;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrSetPrimaryComputername, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRSETPRIMARYCOMPUTERNAME,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrSetPrimaryComputername, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

NTSTATUS rpccli_wkssvc_NetrEnumerateComputerNames(struct rpc_pipe_client *cli,
						  TALLOC_CTX *mem_ctx,
						  const char *server_name /* [in] [unique,charset(UTF16)] */,
						  enum wkssvc_ComputerNameType name_type /* [in]  */,
						  uint32_t Reserved /* [in]  */,
						  struct wkssvc_ComputerNamesCtr **ctr /* [out] [ref] */,
						  WERROR *werror)
{
	struct wkssvc_NetrEnumerateComputerNames r;
	NTSTATUS status;

	/* In parameters */
	r.in.server_name = server_name;
	r.in.name_type = name_type;
	r.in.Reserved = Reserved;

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_IN_DEBUG(wkssvc_NetrEnumerateComputerNames, &r);
	}

	status = cli_do_rpc_ndr(cli,
				mem_ctx,
				&ndr_table_wkssvc,
				NDR_WKSSVC_NETRENUMERATECOMPUTERNAMES,
				&r);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (DEBUGLEVEL >= 10) {
		NDR_PRINT_OUT_DEBUG(wkssvc_NetrEnumerateComputerNames, &r);
	}

	if (NT_STATUS_IS_ERR(status)) {
		return status;
	}

	/* Return variables */
	*ctr = *r.out.ctr;

	/* Return result */
	if (werror) {
		*werror = r.out.result;
	}

	return werror_to_ntstatus(r.out.result);
}

