#ifndef LIBSLIRP_H
#define LIBSLIRP_H

typedef struct Slirp Slirp;

int get_dns_addr(struct in_addr *pdns_addr);
int get_dns6_addr(struct in6_addr *pdns6_addr, uint32_t *scope_id);

/* Changed from QEMU: removed tftp, added if_mtu and if_mru */
Slirp *slirp_init(int restricted, bool in_enabled, struct in_addr vnetwork,
                  struct in_addr vnetmask, struct in_addr vhost,
                  bool in6_enabled,
                  struct in6_addr vprefix_addr6, uint8_t vprefix_len,
                  struct in6_addr vhost6, const char *vhostname,
                  const char *bootfile,
                  struct in_addr vdhcp_start, struct in_addr vnameserver,
                  struct in6_addr vnameserver6, const char **vdnssearch,
                  const char *vdomainname, unsigned int if_mtu, unsigned int if_mru,
                  void *opaque);
void slirp_cleanup(Slirp *slirp);

void slirp_pollfds_fill(GArray *pollfds, uint32_t *timeout);

void slirp_pollfds_poll(GArray *pollfds, int select_error);

void slirp_input(Slirp *slirp, const uint8_t *pkt, int pkt_len);

/* you must provide the following functions: */
void slirp_output(void *opaque, const uint8_t *pkt, int pkt_len);

int slirp_add_hostfwd(Slirp *slirp, int is_udp,
                      struct in_addr host_addr, int host_port,
                      struct in_addr guest_addr, int guest_port);
int slirp_remove_hostfwd(Slirp *slirp, int is_udp,
                         struct in_addr host_addr, int host_port);

/* Changed from QEMU: slirp_add_exec is removed */

/* Changed from QEMU: slirp_connection_info is removed */

void slirp_socket_recv(Slirp *slirp, struct in_addr guest_addr,
                       int guest_port, const uint8_t *buf, int size);
size_t slirp_socket_can_recv(Slirp *slirp, struct in_addr guest_addr,
                             int guest_port);

#endif
