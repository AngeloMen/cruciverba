project('cruciverba', 'c')
src = [ 'AnalisiParametri.c', 'Definizioni.c', 'LeggiDaTastiera.c', 'LeggiDimensioni.c'
       ,'main.c', 'MettiCasella.c', 'PulisciSchema.c', 'GestioneParole.c'
	   ,'RiempiSchema.c', 'StampaDefinizioni.c', 'TrovaParola.c', 'ProssimaParola.c']
mysqldep = dependency('mysqlclient')
executable('cruciverba', sources : src, dependencies : mysqldep, gcc_args : '-ggdb')
