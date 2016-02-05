.. _week-10:

Week - 10 IoT Protocols: RESTful APIs and COAP
**********************************************


REST: Representational State Transfer
=====================================


To see REST in detail follow the `link <http://rest.elkstein.org/>`_

It is stateless, client server, cacheable communnication protocol. e.g HTTP

RESTful applications use HTTP requests to post data (create and/or update), read data (e.g., make queries), and delete data. Thus, REST uses HTTP for all four CRUD (Create/Read/Update/Delete) operations.

REST as Light Weight Web-Service
--------------------------------

As a programming approach, REST is a lightweight alternative to Web Services and RPC.

Much like Web Services, a REST service is:

- Platform-independent (you don't care if the server is Unix, the client is a Mac, or anything else).
- Language-independent (C# can talk to Java, etc.),
- Standards-based (runs on top of HTTP)
- Can easily be used in the presence of firewalls.

Like Web Services, REST offers no built-in security features, encryption, session management, QoS guarantees, etc. But also as with Web Services, these can be added by building on top of HTTP:

For security, username/password tokens are often used.

For encryption, REST can be used on top of HTTPS (secure sockets).
... etc.

Web-Service
===========

A web service is any piece of software that makes itself available over the internet and uses a standardized XML messaging system. XML is used to encode all communications to a web service. For example, a client invokes a web service by sending an XML message, then waits for a corresponding XML response.

Hypertext Transfer Protocol (HTTP) 
==================================

HTTP is a method for encoding and transporting information between a client (such as a web browser) and a web server. HTTP is the primary protocol for transmission of information across the Internet.

Follow the `link for better understanding <https://www.nginx.com/resources/glossary/http/>`_


HTTP follows a request-response paradigm in which the client makes a request and the server issues a response that includes not only the requested content, but also relevant status information about the request.

HTTP is an application layer protocol and relies on an underlying network-level protocol such as Transmission Control Protocol (TCP) to function.

HTTP resources such as web servers are identified across the Internet using unique identifiers known as Uniform Resource Locaters (URLs).


.. _web_name:
.. figure::  images/WEB_NAME_10.jpg
   :align:   center

.. _url_res:
.. figure::  images/URL_RESO_10.jpg
   :align:   center

Follow the link for more understanding: https://en.wikibooks.org/wiki/Communication_Networks/HTTP_Protocol

.. _http_1:
.. figure::  images/HTTP_1_10.jpeg
   :align:   center

.. _http_2:
.. figure::  images/HTTP_2_10.jpeg
   :align:   center

There are two types of messages that HTTP uses

#. Request message 
#. Response message

Request Message
---------------

The request line has three parts, separated by spaces: a method name, the local path of the requested resource and version of HTTP being used. The message format is in ASCII so that it can be read by the humans.
For e.g.:

``GET /path/to/the/file.html HTTP/1.0``

The GET method is the most commonly used. It states that “give me this resource”. The part of the URL is also called as Request URL. The HTTP is to be in uppercase and the next part denotes the version of HTTP.
HTTP Request Message: General Format

The HTTP Request message format is shown below:

.. _http_req_frame:
.. figure::  images/HTTP_REQ_10.png
   :align:   center

The method is the type of method used to request the URL. Like GET, POST or HEAD. The URL block contains the requested URL. Version denotes the HTTP version. Either HTTP/1.0 or HTTP/1.1. The header lines include the browser type, host , number of objects and file name and the type of language in the requested page. For e.g.:

.. _http_req_lines:
.. figure::  images/HTTP_REQ_LINES_10.png
   :align:   center

The entity body is used by the POST method. When user enters information on to the page, the entity body contains that information.

The HTTP 1.0 has GET, POST and HEAD methods. While the HTTP 1.1 has along with GET, POST and HEAD, PUT and DELETE.

Uploading the information in Web pages

The POST method
+++++++++++++++

The Web pages which ask for input from user uses the POST method. The information filled by the web user is uploaded in server’s entity body.
The typical form submission in POST method. The content type is usually the application/x-www-form-urlencoded and the content-type is the length of the URL encoded form data.

The URL method
++++++++++++++

The URL method uses the GET method to get user input from the user. It appends the user information to be uploaded to server to the URL field.

Response Message
----------------

The HTTP message response line also has three parts separated by spaces: the HTTP version, a response status code giving result of the request and English phrase of the status code. This first line is also called as Status line.
The HTTP Response message format is shown below:

.. _http_res:
.. figure::  images/HTTP_RES_10.png
   :align:   center

.. _http_res_lines:
.. figure::  images/HTTP_RES_LINES_10.png
   :align:   center

Below are the some HTTP response status codes:
- 200 OK The request succeeded, and the resulting resource (e.g. file or script output) is returned in the message body.
- 404 Not Found The requested resource doesn't exist.
- 301 Moved Permanently
- 302 Moved Temporarily
- 303 See Other (HTTP 1.1 only)

The resource has moved to another URL (given by the Location: response header), and should be automatically retrieved by the client. This is often used by a CGI script to redirect the browser to an existing file.

- 500 Server Error

An unexpected server error. The most common cause is a server-side script that has bad syntax, fails, or otherwise can't run correctly.

Proxy Server
============

A proxy server is a computer that offers a computer network service to allow clients to make indirect network connections to other network services. A client connects to the proxy server, then requests a connection, file, or other resource available on a different server. The proxy provides the resource either by connecting to the specified server or by serving it from a cache. In some cases, the proxy may alter the client's request or the server's response for various purposes.

Useful Link: http://whatismyipaddress.com/proxy-server

Web Proxies
-----------

A common proxy application is a caching Web proxy. This provides a nearby cache of Web pages and files available on remote Web servers, allowing local network clients to access them more quickly or reliably.

When it receives a request for a Web resource (specified by a URL), a caching proxy looks for the resulting URL in its local cache. If found, it returns the document immediately. Otherwise it fetches it from the remote server, returns it to the requester and saves a copy in the cache. The cache usually uses an expiry algorithm to remove documents from the cache, according to their age, size, and access history. Two simple cache algorithms are Least Recently Used (LRU) and Least Frequently Used (LFU). LRU removes the least-recently used documents, and LFU removes the least-frequently used documents.


COAP – Constrained Application Protocol
=======================================

To learn COAP basic `follow <http://www.coapsharp.com/basics-of-coap/>`_

In the PC world, the message exchange is over TCP and application protocol is HTTP. However, for small devices, implementing the TCP stack and then HTTP protocol is really too much to ask for. That is where CoAP was devised. It’s a tiny protocol at the application layer (an alternative to HTTP) that is envisaged to fit in tiny form factors. It runs on UDP and not on HTTP. The smallest message size that CoAP mandates is 4-bytes! 

**SO IS COAP A REPLACEMENT FOR HTTP**

CoAP is not a replacement for HTTP. It’s an alternative suggestion for tiny devices that have severe resource constraints (e.g. 256 KB memory, 32 KB RAM, 20 MHz speed).

**WHAT ARE THE DIFFERENT TYPES OF COAP MESSAGE**

CoAP messages follow the same request/response paradigm (largely) that is prevelant in HTTP world. There are 4 types of CoAP messages

#. CON – This is called “Confirmable” request. When a CON request is sent, the recipient must respond. 

#. NON – This is called “Non-Confirmable” request. When a NON request is sent, the recipient is not required to respond back. 

#. ACK – This is called “Acknowledgement”. This is a response to a CON message. When processing succeeds, the recipient of a CON message should respond back with an ACK. The ACK message can also contain result of the processing alongwith. 

#. RST – This is called “Reset” message. When the recipient of a message encounters an error, does not understand the message or is no longer interested in the message sender, this response is sent bac

For detailed understanding `follow <http://www.slideshare.net/zdshelby/coap-tutorial>`_

COAP Header Format
------------------

WHAT ARE THE DIFFERENT PARTS OF A COAP MESSAGE

A CoAP message, at minimum, must be 4 bytes long. The different parts, that can make up a CoAP message are:
- Version – What is the CoAP version that this message follows (as of now its V 1) 
- The message type (CON, NON, ACK, RST) 
- The message code (Like PUT, GET, UNAUTHORIZED) 
- The message id. Each CoAP message has an ID associated with it. The ID is generally unique for a conversation for some period of time, after which, it can be recycled. 
- The token. A token is another value that may be attached to the message for matching. Messages can be sent out of order and at that time, token becomes important. 
- A set of options. Options in CoAP are like HTTP request headers. They contain metadata about the CoAP message itself (e.g. the CoAP port, the CoAP host, the CoAP querystring) 
- The payload. This is the actual message that is being exchanged. 


.. _coap_hdr_1:
.. figure::  images/COAP_HEADER_1_10.jpg
   :align:   center

.. _coap_hdr_2:
.. figure::  images/COAP_HEADER_2_10.jpg
   :align:   center

.. _coap_hdr_3:
.. figure::  images/COAP_HEADER_3_10.jpg
   :align:   center

**WHAT IS OBSERVE IN COAP**

Sometimes, you want to monitor a value, let’s say, temperature. In that case, the client does not need to continuously poll the server. The client can send one “Observable” request to the server. From that point onwards, the server will remember the client connection details, and on every change in temperature, will send the new value to the client.If client no longer wishes to receive the temperature values, it can respond back with an RST message and server will clear it’s memory. More on this in examples.

.. _coap_obs:
.. figure::  images/COAP_OBS_10.jpg
   :align:   center


**WHAT IS BLOCK TRANSFER IN COAP**

Given that CoAP messages should be key very small in size, there will be cases when you need to exchange large data streams, either from client to server (like a PUT) or from server to client (like a GET). In that case, the CoAP message can contain options associated with block transfer and then the client and server can exchange multiple messages with blocks of data in each. More on this later on, in tutorials.


.. _coap_obs:
.. figure::  images/COAP_BLOCK_10.jpg
   :align:   center


Logging in Python
-----------------

Logging is way of printing information while running a module. It is just like “printf” but have many advantages over it. import logging 

Another useful feature of the logging API is the ability to produce different messages at different log levels. Let's suppose, I configure the level INFO, then all the log levels above it will be get printed    [20 - 50], while lower will not be printed [0 – 10]. 

Level		Value

========	======

CRITICAL	50
ERROR		40
WARNING		30
INFO		20
DEBUG		10
UNSET		0

========	======

Follow the links for better understanding the logging.

http://victorlin.me/posts/2012/08/26/good-logging-practice-in-python

https://pymotw.com/2/logging/


**What is the difference between functions, sub-routines and co-routines?**

**Function**

A function is basically same just like as it is we use in maths.

 		``F(X) = 2X + 1``

It has some input and based on the expression, it has specific output. Similarly, used in C/C++

int  F (int X)::

	{	return  ((2*X)+1;
	}

**Sub-Routine**

A sub-routine and a function is very much similar except one difference that is, sub-routines does not return anything. It is simply a set of instructions in order to perform a certain task.
We can say that, a void  function is a sub-routine.
 
Both functions and sub-routines have single entry and ending point, and executed completely. 


**Co-Routine**

A co-routine is different from a sub-routine in a way that it has single entry point, multiple ending and re-entry points. That's why we use “resume” co-routine instead of “call” a subroutine.

Co-routine::

   coroutine foo {
    yield 1;
    yield 2;
    yield 3; }
    print foo();
    print foo();
    print foo();
    Prints: 1 2 3


Sub-routine::

    coroutine foo {
    return 1;
    return 2; //Dead code
    return 3;}
    print foo();
    print foo();
    print foo();
    Prints: 1 1 1 

**Note:** Coroutines may use a return, and behave just like a subroutine

For co-routines in Python (generators, yield) follow the link: import asyncio (python library)
http://wla.berkeley.edu/~cs61a/fa11/lectures/streams.html#coroutines
https://www.jeffknupp.com/blog/2013/04/07/improve-your-python-yield-and-generators-explained/

Coap Implementation in Python – aiocoap
---------------------------------------

https://aiocoap.readthedocs.org/en/latest/examples.html

you will want to create a single Context instance that binds to the network.  The Context.create_client_context() and Context.create_server_context() coroutines give you a readily connected context.

On the client side, you can request resources by assembling a Message.

https://aiocoap.readthedocs.org/en/latest/aiocoap.message.html#aiocoap.message.Message

For COAP communication, we will use aiocoap module in Python 3.0+. aicoap module is not yet supported for Python 2.7. Let's install Python 3.0+. 

Check the using version of Python.

``python -V``

To change Python2.7 → Python3.0+

``alias python=python3``

https://aiocoap.readthedocs.org/en/latest/examples.html

COAP Communication in C
-----------------------

libcoap is the COAP communication library for C. 
Download libcoap: https://libcoap.net/
How to use: https://gitlab.informatik.uni-bremen.de/bergmann/libcoap/tree/3e9afb146043a94da25e0e8fc4bc6c03ebc7a2f1/examples


