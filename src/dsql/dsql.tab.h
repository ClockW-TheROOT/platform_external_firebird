#ifndef BISON_DSQL_TAB_H
# define BISON_DSQL_TAB_H

# ifndef YYSTYPE
#  define YYSTYPE int
#  define YYSTYPE_IS_TRIVIAL 1
# endif
# define	ACTIVE	257
# define	ADD	258
# define	AFTER	259
# define	ALL	260
# define	ALTER	261
# define	AND	262
# define	ANY	263
# define	AS	264
# define	ASC	265
# define	AT	266
# define	AVG	267
# define	AUTO	268
# define	BEFORE	269
# define	BEGIN	270
# define	BETWEEN	271
# define	BLOB	272
# define	BY	273
# define	CAST	274
# define	CHARACTER	275
# define	CHECK	276
# define	COLLATE	277
# define	COMMA	278
# define	COMMIT	279
# define	COMMITTED	280
# define	COMPUTED	281
# define	CONCATENATE	282
# define	CONDITIONAL	283
# define	CONSTRAINT	284
# define	CONTAINING	285
# define	COUNT	286
# define	CREATE	287
# define	CSTRING	288
# define	CURRENT	289
# define	CURSOR	290
# define	DATABASE	291
# define	DATE	292
# define	DB_KEY	293
# define	KW_DEBUG	294
# define	DECIMAL	295
# define	DECLARE	296
# define	DEFAULT	297
# define	KW_DELETE	298
# define	DESC	299
# define	DISTINCT	300
# define	DO	301
# define	DOMAIN	302
# define	DROP	303
# define	ELSE	304
# define	END	305
# define	ENTRY_POINT	306
# define	EQL	307
# define	ESCAPE	308
# define	EXCEPTION	309
# define	EXECUTE	310
# define	EXISTS	311
# define	EXIT	312
# define	EXTERNAL	313
# define	FILTER	314
# define	FOR	315
# define	FOREIGN	316
# define	FROM	317
# define	FULL	318
# define	FUNCTION	319
# define	GDSCODE	320
# define	GEQ	321
# define	GENERATOR	322
# define	GEN_ID	323
# define	GRANT	324
# define	GROUP	325
# define	GTR	326
# define	HAVING	327
# define	IF	328
# define	KW_IN	329
# define	INACTIVE	330
# define	INNER	331
# define	INPUT_TYPE	332
# define	INDEX	333
# define	INSERT	334
# define	INTEGER	335
# define	INTO	336
# define	IS	337
# define	ISOLATION	338
# define	JOIN	339
# define	KEY	340
# define	KW_CHAR	341
# define	KW_DEC	342
# define	KW_DOUBLE	343
# define	KW_FILE	344
# define	KW_FLOAT	345
# define	KW_INT	346
# define	KW_LONG	347
# define	KW_NULL	348
# define	KW_NUMERIC	349
# define	KW_UPPER	350
# define	KW_VALUE	351
# define	LENGTH	352
# define	LPAREN	353
# define	LEFT	354
# define	LEQ	355
# define	LEVEL	356
# define	LIKE	357
# define	LSS	358
# define	MANUAL	359
# define	MAXIMUM	360
# define	MAX_SEGMENT	361
# define	MERGE	362
# define	MESSAGE	363
# define	MINIMUM	364
# define	MODULE_NAME	365
# define	NAMES	366
# define	NATIONAL	367
# define	NATURAL	368
# define	NCHAR	369
# define	NEQ	370
# define	NO	371
# define	NOT	372
# define	NOT_GTR	373
# define	NOT_LSS	374
# define	OF	375
# define	ON	376
# define	ONLY	377
# define	OPTION	378
# define	OR	379
# define	ORDER	380
# define	OUTER	381
# define	OUTPUT_TYPE	382
# define	OVERFLOW	383
# define	PAGE	384
# define	PAGES	385
# define	KW_PAGE_SIZE	386
# define	PARAMETER	387
# define	PASSWORD	388
# define	PLAN	389
# define	POSITION	390
# define	POST_EVENT	391
# define	PRECISION	392
# define	PRIMARY	393
# define	PRIVILEGES	394
# define	PROCEDURE	395
# define	PROTECTED	396
# define	READ	397
# define	REAL	398
# define	REFERENCES	399
# define	RESERVING	400
# define	RETAIN	401
# define	RETURNING_VALUES	402
# define	RETURNS	403
# define	REVOKE	404
# define	RIGHT	405
# define	RPAREN	406
# define	ROLLBACK	407
# define	SEGMENT	408
# define	SELECT	409
# define	SET	410
# define	SHADOW	411
# define	KW_SHARED	412
# define	SINGULAR	413
# define	KW_SIZE	414
# define	SMALLINT	415
# define	SNAPSHOT	416
# define	SOME	417
# define	SORT	418
# define	SQLCODE	419
# define	STABILITY	420
# define	STARTING	421
# define	STATISTICS	422
# define	SUB_TYPE	423
# define	SUSPEND	424
# define	SUM	425
# define	TABLE	426
# define	THEN	427
# define	TO	428
# define	TRANSACTION	429
# define	TRIGGER	430
# define	UNCOMMITTED	431
# define	UNION	432
# define	UNIQUE	433
# define	UPDATE	434
# define	USER	435
# define	VALUES	436
# define	VARCHAR	437
# define	VARIABLE	438
# define	VARYING	439
# define	VERSION	440
# define	VIEW	441
# define	WAIT	442
# define	WHEN	443
# define	WHERE	444
# define	WHILE	445
# define	WITH	446
# define	WORK	447
# define	WRITE	448
# define	FLOAT_NUMBER	449
# define	NUMBER	450
# define	NUMERIC	451
# define	SYMBOL	452
# define	STRING	453
# define	INTRODUCER	454
# define	ACTION	455
# define	ADMIN	456
# define	CASCADE	457
# define	FREE_IT	458
# define	RESTRICT	459
# define	ROLE	460
# define	COLUMN	461
# define	TYPE	462
# define	EXTRACT	463
# define	YEAR	464
# define	MONTH	465
# define	DAY	466
# define	HOUR	467
# define	MINUTE	468
# define	SECOND	469
# define	WEEKDAY	470
# define	YEARDAY	471
# define	TIME	472
# define	TIMESTAMP	473
# define	CURRENT_DATE	474
# define	CURRENT_TIME	475
# define	CURRENT_TIMESTAMP	476
# define	NUMBER64BIT	477
# define	SCALEDINT	478
# define	CURRENT_USER	479
# define	CURRENT_ROLE	480
# define	KW_BREAK	481
# define	SUBSTRING	482
# define	RECREATE	483
# define	KW_DESCRIPTOR	484
# define	FIRST	485
# define	SKIP	486
# define	CURRENT_CONNECTION	487
# define	CURRENT_TRANSACTION	488
# define	BIGINT	489
# define	CASE	490
# define	NULLIF	491
# define	COALESCE	492
# define	USING	493
# define	NULLS	494
# define	LAST	495
# define	ROW_COUNT	496
# define	LOCK	497
# define	SAVEPOINT	498
# define	RELEASE	499
# define	STATEMENT	500
# define	LEAVE	501
# define	INSERTING	502
# define	UPDATING	503
# define	DELETING	504
# define	KW_INSERTING	505
# define	KW_UPDATING	506
# define	KW_DELETING	507
# define	BACKUP	508
# define	KW_DIFFERENCE	509
# define	OPEN	510
# define	CLOSE	511
# define	FETCH	512
# define	ROWS	513
# define	BLOCK	514
# define	IIF	515
# define	SCALAR_ARRAY	516
# define	CROSS	517
# define	NEXT	518
# define	SEQUENCE	519
# define	RESTART	520


extern YYSTYPE yylval;

#endif /* not BISON_DSQL_TAB_H */
