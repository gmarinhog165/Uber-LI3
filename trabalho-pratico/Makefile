CC=gcc
GLIB_CFLAGS = $(shell pkg-config --cflags glib-2.0)
GLIB_LIBS = $(shell pkg-config --libs glib-2.0)
CFLAGS = -Wall -Iinclude $(GLIB_CFLAGS)
LDFLAGS = $(GLIB_LIBS) -lm

ODIR = src/obj

$(shell mkdir -p Resultados)

all: programa-principal programa-testes

programa-principal: $(ODIR)/main.o $(ODIR)/drivers.o $(ODIR)/date.o $(ODIR)/users.o $(ODIR)/rides.o $(ODIR)/parse_csv.o $(ODIR)/catalogo_drivers.o $(ODIR)/catalogo_users.o $(ODIR)/catalogo_rides.o $(ODIR)/estatisticas.o $(ODIR)/queries.o $(ODIR)/executer.o $(ODIR)/conector.o $(ODIR)/output.o
	$(CC) $^ $(LDFLAGS) -o $@

programa-testes: $(ODIR)/main_tests.o $(ODIR)/date.o $(ODIR)/drivers.o $(ODIR)/users.o $(ODIR)/rides.o $(ODIR)/parse_csv.o $(ODIR)/catalogo_drivers.o $(ODIR)/catalogo_users.o $(ODIR)/catalogo_rides.o $(ODIR)/estatisticas.o $(ODIR)/conector_testes.o $(ODIR)/queries_tests.o $(ODIR)/executer_tests.o $(ODIR)/output.o
	$(CC) $^ $(LDFLAGS) -o $@

$(ODIR)/%.o: src/%.c
	$(shell mkdir -p $(ODIR))
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f programa-principal programa-testes $(ODIR)/*.o
	rm -rf $(ODIR)
	rm -rf Resultados -f Resultados/*.txt