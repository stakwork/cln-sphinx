#include "config.h"
#include "../amount.c"
#include "../bigsize.c"
#include "../bolt12_merkle.c"
#include "../json.c"
#include "../../wire/fromwire.c"
#include "../../wire/tlvstream.c"
#if EXPERIMENTAL_FEATURES
  #include "../../wire/peer_exp_wiregen.c"
  #include "../../wire/bolt12_exp_wiregen.c"
#else
  #include "../../wire/peer_wiregen.c"
  #include "../../wire/bolt12_wiregen.c"
#endif
#include <ccan/tal/grab_file/grab_file.h>
#include <ccan/tal/path/path.h>
#include <common/channel_type.h>
#include <common/setup.h>

/* AUTOGENERATED MOCKS START */
/* Generated stub for fromwire_channel_id */
void fromwire_channel_id(const u8 **cursor UNNEEDED, size_t *max UNNEEDED,
			 struct channel_id *channel_id UNNEEDED)
{ fprintf(stderr, "fromwire_channel_id called!\n"); abort(); }
/* Generated stub for fromwire_channel_type */
struct channel_type *fromwire_channel_type(const tal_t *ctx UNNEEDED, const u8 **cursor UNNEEDED, size_t *plen UNNEEDED)
{ fprintf(stderr, "fromwire_channel_type called!\n"); abort(); }
/* Generated stub for fromwire_node_id */
void fromwire_node_id(const u8 **cursor UNNEEDED, size_t *max UNNEEDED, struct node_id *id UNNEEDED)
{ fprintf(stderr, "fromwire_node_id called!\n"); abort(); }
/* Generated stub for fromwire_onionmsg_path */
struct onionmsg_path *fromwire_onionmsg_path(const tal_t *ctx UNNEEDED, const u8 **cursor UNNEEDED, size_t *plen UNNEEDED)
{ fprintf(stderr, "fromwire_onionmsg_path called!\n"); abort(); }
/* Generated stub for json_add_member */
void json_add_member(struct json_stream *js UNNEEDED,
		     const char *fieldname UNNEEDED,
		     bool quote UNNEEDED,
		     const char *fmt UNNEEDED, ...)
{ fprintf(stderr, "json_add_member called!\n"); abort(); }
/* Generated stub for json_member_direct */
char *json_member_direct(struct json_stream *js UNNEEDED,
			 const char *fieldname UNNEEDED, size_t extra UNNEEDED)
{ fprintf(stderr, "json_member_direct called!\n"); abort(); }
/* Generated stub for towire */
void towire(u8 **pptr UNNEEDED, const void *data UNNEEDED, size_t len UNNEEDED)
{ fprintf(stderr, "towire called!\n"); abort(); }
/* Generated stub for towire_bool */
void towire_bool(u8 **pptr UNNEEDED, bool v UNNEEDED)
{ fprintf(stderr, "towire_bool called!\n"); abort(); }
/* Generated stub for towire_channel_id */
void towire_channel_id(u8 **pptr UNNEEDED, const struct channel_id *channel_id UNNEEDED)
{ fprintf(stderr, "towire_channel_id called!\n"); abort(); }
/* Generated stub for towire_channel_type */
void towire_channel_type(u8 **p UNNEEDED, const struct channel_type *channel_type UNNEEDED)
{ fprintf(stderr, "towire_channel_type called!\n"); abort(); }
/* Generated stub for towire_node_id */
void towire_node_id(u8 **pptr UNNEEDED, const struct node_id *id UNNEEDED)
{ fprintf(stderr, "towire_node_id called!\n"); abort(); }
/* Generated stub for towire_onionmsg_path */
void towire_onionmsg_path(u8 **p UNNEEDED, const struct onionmsg_path *onionmsg_path UNNEEDED)
{ fprintf(stderr, "towire_onionmsg_path called!\n"); abort(); }
/* Generated stub for towire_secp256k1_ecdsa_signature */
void towire_secp256k1_ecdsa_signature(u8 **pptr UNNEEDED,
			      const secp256k1_ecdsa_signature *signature UNNEEDED)
{ fprintf(stderr, "towire_secp256k1_ecdsa_signature called!\n"); abort(); }
/* Generated stub for towire_sha256 */
void towire_sha256(u8 **pptr UNNEEDED, const struct sha256 *sha256 UNNEEDED)
{ fprintf(stderr, "towire_sha256 called!\n"); abort(); }
/* Generated stub for towire_tu32 */
void towire_tu32(u8 **pptr UNNEEDED, u32 v UNNEEDED)
{ fprintf(stderr, "towire_tu32 called!\n"); abort(); }
/* Generated stub for towire_tu64 */
void towire_tu64(u8 **pptr UNNEEDED, u64 v UNNEEDED)
{ fprintf(stderr, "towire_tu64 called!\n"); abort(); }
/* Generated stub for towire_u16 */
void towire_u16(u8 **pptr UNNEEDED, u16 v UNNEEDED)
{ fprintf(stderr, "towire_u16 called!\n"); abort(); }
/* Generated stub for towire_u32 */
void towire_u32(u8 **pptr UNNEEDED, u32 v UNNEEDED)
{ fprintf(stderr, "towire_u32 called!\n"); abort(); }
/* Generated stub for towire_u64 */
void towire_u64(u8 **pptr UNNEEDED, u64 v UNNEEDED)
{ fprintf(stderr, "towire_u64 called!\n"); abort(); }
/* Generated stub for towire_u8 */
void towire_u8(u8 **pptr UNNEEDED, u8 v UNNEEDED)
{ fprintf(stderr, "towire_u8 called!\n"); abort(); }
/* Generated stub for towire_u8_array */
void towire_u8_array(u8 **pptr UNNEEDED, const u8 *arr UNNEEDED, size_t num UNNEEDED)
{ fprintf(stderr, "towire_u8_array called!\n"); abort(); }
/* Generated stub for towire_utf8_array */
void towire_utf8_array(u8 **pptr UNNEEDED, const char *arr UNNEEDED, size_t num UNNEEDED)
{ fprintf(stderr, "towire_utf8_array called!\n"); abort(); }
/* AUTOGENERATED MOCKS END */

static const struct tlv_field *tlv_to_fields(const tal_t *ctx, const u8 *tlv)
{
	struct tlv_field *fields = tal_arr(ctx, struct tlv_field, 0);
	size_t len = tal_bytelen(tlv);

	/* Dumb parser, assuming it's valid! */
	while (len) {
		struct tlv_field f;
		f.numtype = fromwire_bigsize(&tlv, &len);
		f.length = fromwire_bigsize(&tlv, &len);
		f.value = (u8 *)tlv;
		fromwire(&tlv, &len, NULL, f.length);
		tal_arr_expand(&fields, f);
	}
	return fields;
}

int main(int argc, char *argv[])
{
	char *json;
	size_t i;
	jsmn_parser parser;
	jsmntok_t toks[5000];
	const jsmntok_t *t;

	common_setup(argv[0]);

	if (argv[1])
		json = grab_file(tmpctx, argv[1]);
	else {
		char *dir = getenv("BOLTDIR");
		json = grab_file(tmpctx,
				 path_join(tmpctx,
					   dir ? dir : "../lightning-rfc",
					   "bolt12/merkle-test.json"));
		if (!json) {
			printf("test file not found, skipping\n");
			tal_free(tmpctx);
			exit(0);
		}
	}

	jsmn_init(&parser);
	if (jsmn_parse(&parser, json, strlen(json), toks, ARRAY_SIZE(toks)) < 0)
		abort();

	json_for_each_arr(i, t, toks) {
		const char *tlvtype;
		const u8 *tlv;
		const struct tlv_field *fields;
		struct sha256 merkle, expected_merkle;

		tlvtype = json_strdup(tmpctx, json,
				      json_get_member(json, t, "tlv"));
		tlv = json_tok_bin_from_hex(tmpctx, json,
					    json_get_member(json, t, "all-tlvs"));
		json_to_sha256(json, json_get_member(json, t, "merkle"),
			       &expected_merkle);

		printf("%s:\n", json_strdup(tmpctx, json,
					     json_get_member(json, t, "comment")));

		/* First do it raw. */
		fields = tlv_to_fields(tmpctx, tlv);
		merkle_tlv(fields, &merkle);
		assert(sha256_eq(&merkle, &expected_merkle));
		printf(" - RAW OK\n");

		/* Now do it via type-specific fromwire. */
		if (streq(tlvtype, "n1")) {
			struct tlv_n1 *n1 = tlv_n1_new(tmpctx);
			size_t len = tal_bytelen(tlv);
			assert(fromwire_n1(&tlv, &len, n1));
			assert(len == 0);
			merkle_tlv(n1->fields, &merkle);
			assert(sha256_eq(&merkle, &expected_merkle));
		} else if (streq(tlvtype, "offer")) {
			struct tlv_offer *offer = tlv_offer_new(tmpctx);
			size_t len = tal_bytelen(tlv);
			assert(fromwire_offer(&tlv, &len, offer));
			assert(len == 0);
			merkle_tlv(offer->fields, &merkle);
			assert(sha256_eq(&merkle, &expected_merkle));
		} else
			abort();
		printf(" - WRAPPED OK\n");
	}
	common_shutdown();
	return 0;
}
