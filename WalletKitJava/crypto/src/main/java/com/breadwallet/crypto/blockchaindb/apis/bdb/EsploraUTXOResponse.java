/*
 * Copyright (c) 2020 Hash Engineering Solutions
 *
 * See the LICENSE file at the project root for license information.
 * See the CONTRIBUTORS file at the project root for a list of contributors.
 */
package com.breadwallet.crypto.blockchaindb.apis.bdb;

import com.fasterxml.jackson.annotation.JsonProperty;

/*
    Esoplora response for /api/andress/:address/utxo
    [
        {
            "txid":"36caf59217f34c5f1b2ddb708c84ed27e28b488b61cf613d36d179517d1f0f51",
            "vout":0,
            "status":{
                "confirmed":true,
                "block_height":3348616,
                "block_hash":"00000000000007bcd08c4a4fbbd85b730782f823b268e5f95ca309c71b921503",
                "block_time":1605935614},
                "value":100000
        }
    ]"
 */

public class EsploraUTXOResponse {

    // fields

    @JsonProperty("txid")
    private String txid;

    @JsonProperty("vout")
    private int vout;

    @JsonProperty("status")
    private Status status;

    @JsonProperty("value")
    private int value;

    // getters

    public String getTxid() {
        return txid;
    }

    public int getVout() {
        return vout;
    }

    public Status getStatus() {
        return status;
    }

    public int getValue() {
        return value;
    }

    // internals

    public static class Status {
        @JsonProperty("confirmed")
        public Boolean confirmed;

        @JsonProperty("block_height")
        public int block_height;

        @JsonProperty("block_hash")
        public String block_hash;

        @JsonProperty("block_time")
        public long block_time;

    }
}
