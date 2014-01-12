/* parser auto-generated by pidl */

#include "includes.h"
#include "librpc/gen_ndr/ndr_misc.h"

_PUBLIC_ enum ndr_err_code ndr_push_GUID(struct ndr_push *ndr, int ndr_flags, const struct GUID *r)
{
	if (ndr_flags & NDR_SCALARS) {
		NDR_CHECK(ndr_push_align(ndr, 4));
		NDR_CHECK(ndr_push_uint32(ndr, NDR_SCALARS, r->time_low));
		NDR_CHECK(ndr_push_uint16(ndr, NDR_SCALARS, r->time_mid));
		NDR_CHECK(ndr_push_uint16(ndr, NDR_SCALARS, r->time_hi_and_version));
		NDR_CHECK(ndr_push_array_uint8(ndr, NDR_SCALARS, r->clock_seq, 2));
		NDR_CHECK(ndr_push_array_uint8(ndr, NDR_SCALARS, r->node, 6));
	}
	if (ndr_flags & NDR_BUFFERS) {
	}
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ enum ndr_err_code ndr_pull_GUID(struct ndr_pull *ndr, int ndr_flags, struct GUID *r)
{
	uint32_t size_clock_seq_0 = 0;
	uint32_t size_node_0 = 0;
	if (ndr_flags & NDR_SCALARS) {
		NDR_CHECK(ndr_pull_align(ndr, 4));
		NDR_CHECK(ndr_pull_uint32(ndr, NDR_SCALARS, &r->time_low));
		NDR_CHECK(ndr_pull_uint16(ndr, NDR_SCALARS, &r->time_mid));
		NDR_CHECK(ndr_pull_uint16(ndr, NDR_SCALARS, &r->time_hi_and_version));
		size_clock_seq_0 = 2;
		NDR_CHECK(ndr_pull_array_uint8(ndr, NDR_SCALARS, r->clock_seq, size_clock_seq_0));
		size_node_0 = 6;
		NDR_CHECK(ndr_pull_array_uint8(ndr, NDR_SCALARS, r->node, size_node_0));
	}
	if (ndr_flags & NDR_BUFFERS) {
	}
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ size_t ndr_size_GUID(const struct GUID *r, int flags)
{
	return ndr_size_struct(r, flags, (ndr_push_flags_fn_t)ndr_push_GUID);
}

_PUBLIC_ enum ndr_err_code ndr_push_ndr_syntax_id(struct ndr_push *ndr, int ndr_flags, const struct ndr_syntax_id *r)
{
	if (ndr_flags & NDR_SCALARS) {
		NDR_CHECK(ndr_push_align(ndr, 4));
		NDR_CHECK(ndr_push_GUID(ndr, NDR_SCALARS, &r->uuid));
		NDR_CHECK(ndr_push_uint32(ndr, NDR_SCALARS, r->if_version));
	}
	if (ndr_flags & NDR_BUFFERS) {
	}
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ enum ndr_err_code ndr_pull_ndr_syntax_id(struct ndr_pull *ndr, int ndr_flags, struct ndr_syntax_id *r)
{
	if (ndr_flags & NDR_SCALARS) {
		NDR_CHECK(ndr_pull_align(ndr, 4));
		NDR_CHECK(ndr_pull_GUID(ndr, NDR_SCALARS, &r->uuid));
		NDR_CHECK(ndr_pull_uint32(ndr, NDR_SCALARS, &r->if_version));
	}
	if (ndr_flags & NDR_BUFFERS) {
	}
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ void ndr_print_ndr_syntax_id(struct ndr_print *ndr, const char *name, const struct ndr_syntax_id *r)
{
	ndr_print_struct(ndr, name, "ndr_syntax_id");
	ndr->depth++;
	ndr_print_GUID(ndr, "uuid", &r->uuid);
	ndr_print_uint32(ndr, "if_version", r->if_version);
	ndr->depth--;
}

_PUBLIC_ enum ndr_err_code ndr_push_policy_handle(struct ndr_push *ndr, int ndr_flags, const struct policy_handle *r)
{
	if (ndr_flags & NDR_SCALARS) {
		NDR_CHECK(ndr_push_align(ndr, 4));
		NDR_CHECK(ndr_push_uint32(ndr, NDR_SCALARS, r->handle_type));
		NDR_CHECK(ndr_push_GUID(ndr, NDR_SCALARS, &r->uuid));
	}
	if (ndr_flags & NDR_BUFFERS) {
	}
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ enum ndr_err_code ndr_pull_policy_handle(struct ndr_pull *ndr, int ndr_flags, struct policy_handle *r)
{
	if (ndr_flags & NDR_SCALARS) {
		NDR_CHECK(ndr_pull_align(ndr, 4));
		NDR_CHECK(ndr_pull_uint32(ndr, NDR_SCALARS, &r->handle_type));
		NDR_CHECK(ndr_pull_GUID(ndr, NDR_SCALARS, &r->uuid));
	}
	if (ndr_flags & NDR_BUFFERS) {
	}
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ void ndr_print_policy_handle(struct ndr_print *ndr, const char *name, const struct policy_handle *r)
{
	ndr_print_struct(ndr, name, "policy_handle");
	ndr->depth++;
	ndr_print_uint32(ndr, "handle_type", r->handle_type);
	ndr_print_GUID(ndr, "uuid", &r->uuid);
	ndr->depth--;
}

_PUBLIC_ enum ndr_err_code ndr_push_netr_SchannelType(struct ndr_push *ndr, int ndr_flags, enum netr_SchannelType r)
{
	NDR_CHECK(ndr_push_uint16(ndr, NDR_SCALARS, r));
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ enum ndr_err_code ndr_pull_netr_SchannelType(struct ndr_pull *ndr, int ndr_flags, enum netr_SchannelType *r)
{
	uint16_t v;
	NDR_CHECK(ndr_pull_uint16(ndr, NDR_SCALARS, &v));
	*r = v;
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ void ndr_print_netr_SchannelType(struct ndr_print *ndr, const char *name, enum netr_SchannelType r)
{
	const char *val = NULL;

	switch (r) {
		case SEC_CHAN_WKSTA: val = "SEC_CHAN_WKSTA"; break;
		case SEC_CHAN_DOMAIN: val = "SEC_CHAN_DOMAIN"; break;
		case SEC_CHAN_BDC: val = "SEC_CHAN_BDC"; break;
	}
	ndr_print_enum(ndr, name, "ENUM", val, r);
}

_PUBLIC_ enum ndr_err_code ndr_push_netr_SamDatabaseID(struct ndr_push *ndr, int ndr_flags, enum netr_SamDatabaseID r)
{
	NDR_CHECK(ndr_push_uint32(ndr, NDR_SCALARS, r));
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ enum ndr_err_code ndr_pull_netr_SamDatabaseID(struct ndr_pull *ndr, int ndr_flags, enum netr_SamDatabaseID *r)
{
	uint32_t v;
	NDR_CHECK(ndr_pull_uint32(ndr, NDR_SCALARS, &v));
	*r = v;
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ void ndr_print_netr_SamDatabaseID(struct ndr_print *ndr, const char *name, enum netr_SamDatabaseID r)
{
	const char *val = NULL;

	switch (r) {
		case SAM_DATABASE_DOMAIN: val = "SAM_DATABASE_DOMAIN"; break;
		case SAM_DATABASE_BUILTIN: val = "SAM_DATABASE_BUILTIN"; break;
		case SAM_DATABASE_PRIVS: val = "SAM_DATABASE_PRIVS"; break;
	}
	ndr_print_enum(ndr, name, "ENUM", val, r);
}

_PUBLIC_ enum ndr_err_code ndr_push_samr_RejectReason(struct ndr_push *ndr, int ndr_flags, enum samr_RejectReason r)
{
	NDR_CHECK(ndr_push_uint32(ndr, NDR_SCALARS, r));
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ enum ndr_err_code ndr_pull_samr_RejectReason(struct ndr_pull *ndr, int ndr_flags, enum samr_RejectReason *r)
{
	uint32_t v;
	NDR_CHECK(ndr_pull_uint32(ndr, NDR_SCALARS, &v));
	*r = v;
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ void ndr_print_samr_RejectReason(struct ndr_print *ndr, const char *name, enum samr_RejectReason r)
{
	const char *val = NULL;

	switch (r) {
		case SAMR_REJECT_OTHER: val = "SAMR_REJECT_OTHER"; break;
		case SAMR_REJECT_TOO_SHORT: val = "SAMR_REJECT_TOO_SHORT"; break;
		case SAMR_REJECT_IN_HISTORY: val = "SAMR_REJECT_IN_HISTORY"; break;
		case SAMR_REJECT_COMPLEXITY: val = "SAMR_REJECT_COMPLEXITY"; break;
	}
	ndr_print_enum(ndr, name, "ENUM", val, r);
}

