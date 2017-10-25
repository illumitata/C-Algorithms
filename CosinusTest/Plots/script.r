#pakiety ggplot2 i rschape2

macFront <- read.csv("macfrontdiff.csv", head=T, sep=',')
macBack <- read.csv("macbackdiff.csv", head=T, sep=',')
nextFront <- read.csv("nextfrontdiff.csv", head=T, sep=',')
nextBack <- read.csv("nextbackdiff.csv", head=T, sep=',')

df <- data.frame(krok=macFront$krok, y1=macFront$error, y2=macBack$error, y3=nextFront$error, y3=nextBack$error)

df.m <- melt(df, id = "krok")

graf <- ggplot(data = df.m, aes(x=krok, y=value, color=variable)) +
geom_point(size = 1.0, position=position_dodge(width=0.8)) +
labs(title = "Błąd bezwzględny metody dla zakresu (-π, +π)", subtitle = "obliczony względem funkcji 'cos' z biblioteki 'math.h'\n", x = "Krok w rozwinięciu wzoru Maclaurina", y = "Popełniany błąd", color = "Metoda\n", caption="(wyk.1)") +
scale_color_manual(labels = c("Z definicji od przodu", "Z definicji od tyłu", "Z poprzedniego wyrazu od przodu", "Z poprzedniego wyrazu od tyłu"), values = c("blue", "red", "green", "yellow"))+
theme(text=element_text(size=10, family="Arial")) +
guides(colour = guide_legend(override.aes = list(size=10)))

graf <- graf + scale_y_log10()

skala <- c(1,2,3,4,5,10,15,20,25,30,31,32,33,34,35,40,50)

graf <- graf + scale_x_continuous(breaks=skala)

ggsave(file="wykres_cos.png", width=12, height=6, dpi=300)

############################


#dla jednej z iteracji
elo  <- macFront[seq(6285*4, 6285*5, 1),2]
elo1 <- macFront[seq(6285*5, 6285*6, 1),3]
elo2 <- macFront[seq(6285*10, 6285*11, 1),3]
elo3 <- macFront[seq(6285*20, 6285*21, 1),3]
elo4 <- macFront[seq(6285*35, 6285*36, 1),3]

df2 <- data.frame(radian=elo, y1=elo1, y2=elo2, y3=elo3, y4=elo4)

df2.m <- melt(df2, id="radian")
graf2 <- ggplot(data = df2.m, aes(x=radian, y=value, color=variable)) +
geom_point(size = 0.5) +
labs(subtitle = "Sumowanie przy pomocy definicji od przodu\n", x = "Wartość w radianach", y = "Popełniany błąd bezwzględny", color="Iteracja\n", caption="(wyk.2)") +
scale_color_manual(labels = c("5", "10", "20", "35"), values = c("#a0a0e5","#7676db", "#4545d8", "#e800aa"))+
theme(text=element_text(size=10, family="Arial")) +
guides(colour = guide_legend(override.aes = list(size=10)))

graf2 <- graf2 + scale_y_log10() + scale_x_continuous(breaks=c(-3.14, 0, 3.14))

ggsave(file="frontMac.png", width=5, height=4, dpi=300)


###########################ITERACJE 5 - 10 - 20 - 35

elo  <- macBack[seq(6285*4, 6285*5, 1),2]
elo1 <- macBack[seq(6285*5, 6285*6, 1),3]
elo2 <- macBack[seq(6285*10, 6285*11, 1),3]
elo3 <- macBack[seq(6285*20, 6285*21, 1),3]
elo4 <- macBack[seq(6285*35, 6285*36, 1),3]

df2 <- data.frame(radian=elo, y1=elo1, y2=elo2, y3=elo3, y4=elo4)

df2.m <- melt(df2, id="radian")
graf3 <- ggplot(data = df2.m, aes(x=radian, y=value, color=variable)) +
geom_point(size = 0.5) +
labs(subtitle = "Sumowanie przy pomocy definicji od tyłu\n", x = "Wartość w radianach", y = "Popełniany błąd bezwzględny", color="Iteracja\n", caption="(wyk.3)") +
scale_color_manual(labels = c("5", "10", "20", "35"), values = c("#e08484","#db5353", "#db2b2b", "#e800aa"))+
theme(text=element_text(size=10, family="Arial")) +
guides(colour = guide_legend(override.aes = list(size=10)))

graf3 <- graf3 + scale_y_log10() + scale_x_continuous(breaks=c(-3.14, 0, 3.14))

ggsave(file="backMac.png", width=5, height=4, dpi=300)

############################

elo  <- nextFront[seq(6285*4, 6285*5, 1),2]
elo1 <- nextFront[seq(6285*5, 6285*6, 1),3]
elo2 <- nextFront[seq(6285*10, 6285*11, 1),3]
elo3 <- nextFront[seq(6285*20, 6285*21, 1),3]
elo4 <- nextFront[seq(6285*35, 6285*36, 1),3]

df2 <- data.frame(radian=elo, y1=elo1, y2=elo2, y3=elo3, y4=elo4)

df2.m <- melt(df2, id="radian")
graf4 <- ggplot(data = df2.m, aes(x=radian, y=value, color=variable)) +
geom_point(size = 0.5) +
labs(subtitle = "Sumowanie przez poprzedni wyraz od przodu\n", x = "Wartość w radianach", y = "Popełniany błąd bezwzględny", color="Iteracja\n", caption="(wyk.4)") +
scale_color_manual(labels = c("5", "10", "20", "35"), values = c("#9ddb9f","#23ce42", "#3ca81e", "#04ff00"))+
theme(text=element_text(size=10, family="Arial")) +
guides(colour = guide_legend(override.aes = list(size=10)))

graf4 <- graf4 + scale_y_log10() + scale_x_continuous(breaks=c(-3.14, 0, 3.14))

ggsave(file="nextFront.png", width=5, height=4, dpi=300)

#############################

elo  <- nextBack[seq(6285*4, 6285*5, 1),2]
elo1 <- nextBack[seq(6285*5, 6285*6, 1),3]
elo2 <- nextBack[seq(6285*10, 6285*11, 1),3]
elo3 <- nextBack[seq(6285*20, 6285*21, 1),3]
elo4 <- nextBack[seq(6285*35, 6285*36, 1),3]

df2 <- data.frame(radian=elo, y1=elo1, y2=elo2, y3=elo3, y4=elo4)

df2.m <- melt(df2, id="radian")
graf5 <- ggplot(data = df2.m, aes(x=radian, y=value, color=variable)) +
geom_point(size = 0.5) +
labs(subtitle = "Sumowanie przez poprzedni wyraz od tyłu\n", x = "Wartość w radianach", y = "Popełniany błąd bezwzględny", color="Iteracja\n", caption="(wyk.5)") +
scale_color_manual(labels = c("5", "10", "20", "35"), values = c("#d1d138","#e0e01a", "#f2f207", "#ffff00"))+
theme(text=element_text(size=10, family="Arial")) +
guides(colour = guide_legend(override.aes = list(size=10)))

graf5 <- graf5 + scale_y_log10() + scale_x_continuous(breaks=c(-3.14, 0, 3.14))

ggsave(file="nextBack.png", dpi=300, width=5, height=4)

##############################

combine <- ggarrange(graf2, graf3, graf4, graf5, ncol=1, nrow=4) +
theme(text=element_text(size=10, family="Arial")) +
theme(plot.margin = unit(c(1,1,1,1), "cm"))

ggsave(file="combine.png", dpi=300, width=4, height=16)

