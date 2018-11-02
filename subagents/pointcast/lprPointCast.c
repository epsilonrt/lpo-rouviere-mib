/*
 * Note: this file originally auto-generated by mib2c using
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <modbus.h>
#include <Arduino.h>
#include <errno.h>
#include "lprPointCast.h"

#define MB_CTOR_COILS 3

// Modbus Config
static double mbTimeout = 1.0;
static int mbCtorSlave = 8;
static unsigned long mbPollDelay = 5000;

// RTU
static char mbRtuPort[] = "/dev/ttyUSB0";
static int mbRtuBaud = 19200;
static char mbRtuParity = 'E';
static int mbRtuDatabit = 8;
static int mbRtuStopbit = 1;

// Global variables
int dodebug = 1;
static uint8_t coil[MB_CTOR_COILS];
static  modbus_t * mb;

int
snmp_get_do_debugging (void) {
  return dodebug;
}

/** Initializes the lprPointCast module */
int
init_lprPointCast (int debug) {
  const oid coil1_oid[] = { 1, 3, 6, 1, 4, 1, 52900, 1, 2, 1, 1 };
  const oid coil2_oid[] = { 1, 3, 6, 1, 4, 1, 52900, 1, 2, 1, 2 };
  const oid coil3_oid[] = { 1, 3, 6, 1, 4, 1, 52900, 1, 2, 1, 3 };

  DEBUGMSGTL ( ("lprPointCast", "Initializing\n"));

  mb = modbus_new_rtu (mbRtuPort, mbRtuBaud, mbRtuParity,
                       mbRtuDatabit, mbRtuStopbit);
  if (mb == NULL) {

    snmp_log (LOG_ERR, "Unable to create the libmodbus context\n");
    return SNMP_ERR_GENERR;
  }

  modbus_set_debug (mb, debug);

  if (modbus_connect (mb) == -1) {

    snmp_log (LOG_ERR, "Modbus connection failed: %s\n", modbus_strerror (errno));
    modbus_free (mb);
    return SNMP_ERR_GENERR;
  }

  /*
   * avoid that the slave takes the pulse of 40μs created by the driver when
   * opening the port as a start bit.
   */
  delay (20);

#if  LIBMODBUS_VERSION_MAJOR >= 3
#if  LIBMODBUS_VERSION_MINOR >= 1
  uint32_t  sec, usec;
  sec = (uint32_t) mbTimeout;
  usec = (uint32_t) ( (mbTimeout - sec) * 1E6);
  modbus_set_response_timeout (mb, sec, usec);
#else
  struct timeval response_timeout;
  response_timeout.tv_sec = (time_t) mbTimeout;
  response_timeout.tv_usec = (time_t) ( (mbTimeout - response_timeout.tv_sec) * 1E6);
  modbus_set_response_timeout (mb, &response_timeout);
#endif
#endif

  modbus_set_slave (mb, mbCtorSlave);

  netsnmp_register_scalar (
    netsnmp_create_handler_registration ("coil1", handle_coil1,
                                         coil1_oid, OID_LENGTH (coil1_oid),
                                         HANDLER_CAN_RWRITE
                                        ));
  netsnmp_register_scalar (
    netsnmp_create_handler_registration ("coil2", handle_coil2,
                                         coil2_oid, OID_LENGTH (coil2_oid),
                                         HANDLER_CAN_RWRITE
                                        ));
  netsnmp_register_scalar (
    netsnmp_create_handler_registration ("coil3", handle_coil3,
                                         coil3_oid, OID_LENGTH (coil3_oid),
                                         HANDLER_CAN_RWRITE
                                        ));
  return SNMP_ERR_NOERROR;
}

void
poll_lprPointCast (void) {
  static unsigned long prevTime;

  if ( (millis() - prevTime) >= mbPollDelay) {

    prevTime = millis();
    if (modbus_read_bits (mb, 0, MB_CTOR_COILS, coil) != MB_CTOR_COILS) {

      snmp_log (LOG_ERR, "Modbus read failed: %s\n", modbus_strerror (errno));
    }
  }
}

int
handle_coil (netsnmp_agent_request_info *reqinfo,
             netsnmp_request_info *requests,
             int i) {

  int ret;

  switch (reqinfo->mode) {

    case MODE_GET:
      snmp_set_var_typed_value (requests->requestvb, ASN_INTEGER,
                                (u_char *) &coil[i],
                                sizeof (coil[i]));
      DEBUGMSGTL ( ("lprPointCast", "coil%d current value :  %d\n", i + 1, coil[i]));
      break;

      /*
       * SET REQUEST
       *
       * multiple states in the transaction.  See:
       * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
       */
    case MODE_SET_RESERVE1:
      /* or you could use netsnmp_check_vb_type_and_size instead */
      ret = netsnmp_check_vb_type (requests->requestvb, ASN_INTEGER);
      if (ret != SNMP_ERR_NOERROR) {
        netsnmp_set_request_error (reqinfo, requests, ret);
        return SNMP_ERR_GENERR;
      }
      break;

    case MODE_SET_RESERVE2:
      break;

    case MODE_SET_FREE:
      break;

    case MODE_SET_ACTION:
      if ( (i < 0) || (i >= MB_CTOR_COILS)) {
        netsnmp_set_request_error (reqinfo, requests, -1);
        return SNMP_ERR_GENERR;
      }
      coil[i] = * (requests->requestvb->val.integer);
      if (modbus_write_bit (mb, i, coil[i]) != 1) {

        snmp_log (LOG_ERR, "Modbus write failed: %s\n", modbus_strerror (errno));
        return SNMP_ERR_GENERR;
      }
      DEBUGMSGTL ( ("lprPointCast", "coil%d set now to %d\n", i + 1, coil[i]));
      break;

    case MODE_SET_COMMIT:
      break;

    case MODE_SET_UNDO:
      break;

    default:
      /* we should never get here, so this is a really bad error */
      snmp_log (LOG_ERR, "unknown mode (%d) in handle_led%d\n", reqinfo->mode, i);
      return SNMP_ERR_GENERR;
  }

  return SNMP_ERR_NOERROR;
}

int
handle_coil1 (netsnmp_mib_handler *handler,
              netsnmp_handler_registration *reginfo,
              netsnmp_agent_request_info   *reqinfo,
              netsnmp_request_info         *requests) {
  return handle_coil (reqinfo, requests, 0);
}

int
handle_coil2 (netsnmp_mib_handler *handler,
              netsnmp_handler_registration *reginfo,
              netsnmp_agent_request_info   *reqinfo,
              netsnmp_request_info         *requests) {
  return handle_coil (reqinfo, requests, 1);
}

int
handle_coil3 (netsnmp_mib_handler *handler,
              netsnmp_handler_registration *reginfo,
              netsnmp_agent_request_info   *reqinfo,
              netsnmp_request_info         *requests) {
  return handle_coil (reqinfo, requests, 2);
}
