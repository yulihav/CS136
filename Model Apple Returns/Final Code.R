#--------------------------------------------------------------------------------
# Stat 331 Final Project Code
# Christopher Salahub, 20502903
# Yuliana Havryshchuk, 20514228
#--------------------------------------------------------------------------------


#--- important functions --------------------------------------------------------
# format dataset to get tomorrow's returns and data up to today, with
# 'log' and 'scaled' indicating whether the values returned should be
# transformed with logarithms and scaled respectively
ret.format.Xy <- function(ret.name, cov.names, p, data, 
                          log = FALSE, scale = FALSE) {
  n <- nrow(data)
  data2 <- matrix(NA, n-p-1, length(cov.names)*(p+1) + 1)
  data2 <- as.data.frame(data2)
  # format design matrix to produce past dependence
  AR.format.X <- function(x, p) {
    p <- p+1
    n <- length(x)
    X <- matrix(NA, n-p+1, p)
    for(ii in 1:p) {
      X[,ii] <- x[1:(n-p+1)+(p-ii)]
    }
    X
  }
  # covariates
  for(ii in 1:length(cov.names)) {
    cind <- 1 + (p+1)*(ii-1)+1:(p+1) # column indices
    data2[,cind] <- AR.format.X(data[-n,cov.names[ii]], p = p)
    names(data2)[cind] <- paste0(cov.names[ii], 0:p)
  }
  # response
  data2[,1] <- exp(diff(log(data[(p+1):nrow(data),ret.name])))-1
  names(data2)[1] <- paste0("ret.", ret.name)
  # scale and transform response if desired
  if (log) {
    data2[,1] <- data2[,1] + 1
    data2 <- log(data2)
  }
  if (scale) {
    data2 <- data2/sqrt(vol[p:(n-p-1)])
  }
  # add dates
  data2[,(ncol(data2)+1)] <- AR.format.X(dates[2:n], p = p)[,1]
  names(data2)[ncol(data2)] <- 'Date'
  data2
}

# Preparation: getting and organizing data, general plots------------------------
# load data
market <- read.csv("market_index_clean.csv")
market$Date <- as.Date(market$Date) # format date

head(market)

# The following plots were used for understanding the data; Not in report 
# plot Apple stock and returns, log returns, and volatily scaled returns
ndays <- nrow(market)
AAPL <- market$AAPL
vol <- market$VIX
# normal returns
ret.AAPL <- (AAPL[2:ndays]-AAPL[1:(ndays-1)])/AAPL[1:(ndays-1)]
# log returns
log.ret.AAPL <- log(ret.AAPL + 1)
# scaled returns
ret.AAPLw <- ret.AAPL/sqrt(vol[1:(ndays-1)])
# scaled log returns
log.ret.AAPLw <- log.ret.AAPL/sqrt(vol[1:(ndays-1)])
dates <- as.Date(market$Date)

# plot normal returns
par(mfrow = c(1,2), mar = c(4, 4, 1, 1)+.1)
plot(Date, AAPL, pch = 16, cex = .5,
     xaxt = "n", xlab = "Date", ylab = "APPL Stock")
axis.Date(side = 1, x = Date, format = "%b'%y")
plot(Date[1:(ndays-1)], ret.AAPL, pch = 16, cex = .5,
     xaxt = "n", xlab = "Date", ylab = "APPL Returns")
axis.Date(side = 1, x = Date[1:(ndays-1)], format = "%b'%y")

# plot log returns
par(mfrow = c(1,2), mar = c(4, 4, 1, 1)+.1)
plot(dates, AAPL, pch = 16, cex = .5,
     xaxt = "n", xlab = "Date", ylab = "APPL Stock")
axis.Date(side = 1, x = dates, format = "%b'%y")
plot(dates[1:(ndays-1)], log.ret.AAPL, pch = 16, cex = .5,
     xaxt = "n", xlab = "Date", ylab = "Log Returns")
axis.Date(side = 1, x = dates[1:(ndays-1)], format = "%b'%y")

# plot scaled returns
par(mfrow = c(1,2), mar = c(4, 4, 1, 1)+.1)
plot(dates, AAPL, pch = 16, cex = .5,
     xaxt = "n", xlab = "Date", ylab = "APPL Stock")
axis.Date(side = 1, x = dates, format = "%b'%y")
plot(dates[1:(ndays-1)], ret.AAPLw, pch = 16, cex = .5,
     xaxt = "n", xlab = "Date", ylab = "Scaled Returns")
axis.Date(side = 1, x = dates[1:(ndays-1)], format = "%b'%y")

# plot scaled log returns
par(mfrow = c(1,2), mar = c(4, 4, 1, 1)+.1)
plot(dates, AAPL, pch = 16, cex = .5,
     xaxt = "n", xlab = "Date", ylab = "APPL Stock")
axis.Date(side = 1, x = dates, format = "%b'%y")
plot(dates[1:(ndays-1)], log.ret.AAPLw, pch = 16, cex = .5,
     xaxt = "n", xlab = "Date", ylab = "Scaled Log Returns")
axis.Date(side = 1, x = dates[1:(ndays-1)], format = "%b'%y")

# there are some indications here that the variance of the returns may
# be heteroscedastic, but lets fit a simple model first and see what the
# results are, notice that scaling placed a number of extreme points back
# in the general body of points


# SECTION 2.2: MODEL SELECTION -------------------------------------------

# SECTION 2.2 ------------------------------------------------------------
# CREATING THE MODELS ----------------------------------------------------

# let's generate all the data frames we need for the data
ret.name <- 'AAPL'
cov.names <- c('AAPL', 'SPX', 'VIX', 'SPGSCITR', 'BNDGLB', 'EEM')
# 11-term data frames
p <- 10
mdata10 <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                         p = p, data = market)
mdata10scl <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                            p = p, data = market, scale = TRUE)
mdata10log <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                            p = p, data = market, log = TRUE)
mdata10ls <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                           p = p, data = market, log = TRUE, scale = TRUE)
# 3-term data frames
p <- 2
mdata3 <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                        p = p, data = market)
mdata3scl <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                           p = p, data = market, scale = TRUE)
mdata3log <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                           p = p, data = market, log = TRUE)
mdata3ls <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                          p = p, data = market, log = TRUE, scale = TRUE)
# 1-term data frames
p <- 0
mdata1 <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                        p = p, data = market)
mdata1scl <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                           p = p, data = market, scale = TRUE)
mdata1log <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                           p = p, data = market, log = TRUE)
mdata1ls <- ret.format.Xy(ret.name = ret.name, cov.names = cov.names,
                          p = p, data = market, log = TRUE, scale = TRUE)

# this data is too large to do a pairs plot, so let's look at a pairs plot
# of just the first terms from today
# THIS PLOT CAN BE SEEN IN FIGURE 1, SECTION 2.2
par(pch = 20)
pairs1 <- cbind(mdata10$ret.AAPL, mdata10$AAPL0, mdata10$SPX0, mdata10$VIX0,
               mdata10$SPGSCITR0, mdata10$BNDGLB0, mdata10$EEM0)
colnames(pairs1) <- append('ret.AAPL', cov.names)
pairs(pairs1, main = 'Day Before Untransformed Pairs Plots')
# and with the scaled data
pairs1scl <- cbind(mdata10scl$ret.AAPL, mdata10scl$AAPL0, mdata10scl$SPX0, mdata10scl$VIX0,
                 mdata10scl$SPGSCITR0, mdata10scl$BNDGLB0, mdata10scl$EEM0)
colnames(pairs1scl) <- append('scl.ret.AAPL', sapply(cov.names, function(nm) paste('scl.', nm)))
pairs(pairs1scl, main = 'Day Before Scaled Pairs Plots')
# and the log data
pairs1log <- cbind(mdata10log$ret.AAPL, mdata10log$AAPL0, mdata10log$SPX0, mdata10log$VIX0,
                   mdata10log$SPGSCITR0, mdata10log$BNDGLB0, mdata10log$EEM0)
colnames(pairs1log) <- append('log.ret.AAPL', sapply(cov.names, function(nm) paste('log.', nm)))
pairs(pairs1log, main = 'Day Before Log Pairs Plots')

# and the log-scaled data
pairs1ls <- cbind(mdata10ls$ret.AAPL, mdata10ls$AAPL0, mdata10ls$SPX0, mdata10ls$VIX0,
                   mdata10ls$SPGSCITR0, mdata10ls$BNDGLB0, mdata10ls$EEM0)
colnames(pairs1ls) <- append('ls.ret.AAPL', sapply(cov.names, function(nm) paste('ls.', nm)))
pairs(pairs1ls, main = 'Day Before Log-Scaled Pairs Plots')

# let's repeat those pairs plots for two days before and three days before
# for two days before
# THIS PLOT CAN BE SEEN IN THE APPENDIX, FIGURE A1
pairs2 <- cbind(mdata10$ret.AAPL, mdata10$AAPL1, mdata10$SPX1, mdata10$VIX1,
                mdata10$SPGSCITR1, mdata10$BNDGLB1, mdata10$EEM1)
colnames(pairs2) <- append('ret.AAPL', cov.names)
pairs(pairs2, main = 'Two Days Before Untransformed Pairs Plots')
pairs2scl <- cbind(mdata10scl$ret.AAPL, mdata10scl$AAPL1, mdata10scl$SPX1, mdata10scl$VIX1,
                   mdata10scl$SPGSCITR1, mdata10scl$BNDGLB1, mdata10scl$EEM1)
colnames(pairs2scl) <- append('scl.ret.AAPL', sapply(cov.names, function(nm) paste('scl.', nm)))
pairs(pairs2scl, main = 'Two Days Before Scaled Pairs Plots')
pairs2log <- cbind(mdata10log$ret.AAPL, mdata10log$AAPL1, mdata10log$SPX1, mdata10log$VIX1,
                   mdata10log$SPGSCITR1, mdata10log$BNDGLB1, mdata10log$EEM1)
colnames(pairs2log) <- append('log.ret.AAPL', sapply(cov.names, function(nm) paste('log.', nm)))
pairs(pairs2log, main = 'Two Days Before Log Pairs Plots')
pairs2ls <- cbind(mdata10ls$ret.AAPL, mdata10ls$AAPL1, mdata10ls$SPX1, mdata10ls$VIX1,
                  mdata10ls$SPGSCITR1, mdata10ls$BNDGLB1, mdata10ls$EEM1)
colnames(pairs2ls) <- append('ls.ret.AAPL', sapply(cov.names, function(nm) paste('ls.', nm)))
pairs(pairs2ls, main = 'Two Days Before Log-Scaled Pairs Plots')

# and for three days before
# THIS PLOT CAN BE SEEN IN THE APPENDIX, FIGURE A1
pairs3 <- cbind(mdata10$ret.AAPL, mdata10$AAPL2, mdata10$SPX2, mdata10$VIX2,
                mdata10$SPGSCITR2, mdata10$BNDGLB2, mdata10$EEM2)
colnames(pairs3) <- append('ret.AAPL', cov.names)
pairs(pairs3, main = 'Three Days Before Untransformed Pairs Plots')
pairs3scl <- cbind(mdata10scl$ret.AAPL, mdata10scl$AAPL2, mdata10scl$SPX2, mdata10scl$VIX2,
                   mdata10scl$SPGSCITR2, mdata10scl$BNDGLB2, mdata10scl$EEM2)
colnames(pairs3scl) <- append('scl.ret.AAPL', sapply(cov.names, function(nm) paste('scl.', nm)))
pairs(pairs3scl, main = 'Three Days Before Scaled Pairs Plots')
pairs3log <- cbind(mdata10log$ret.AAPL, mdata10log$AAPL2, mdata10log$SPX2, mdata10log$VIX2,
                   mdata10log$SPGSCITR2, mdata10log$BNDGLB2, mdata10log$EEM2)
colnames(pairs3log) <- append('log.ret.AAPL', sapply(cov.names, function(nm) paste('log.', nm)))
pairs(pairs3log, main = 'Three Days Before Log Pairs Plots')
pairs3ls <- cbind(mdata10ls$ret.AAPL, mdata10ls$AAPL2, mdata10ls$SPX2, mdata10ls$VIX2,
                  mdata10ls$SPGSCITR2, mdata10ls$BNDGLB2, mdata10ls$EEM2)
colnames(pairs3ls) <- append('ls.ret.AAPL', sapply(cov.names, function(nm) paste('ls.', nm)))
pairs(pairs3ls, main = 'Three Days Before Log-Scaled Pairs Plots')

par(pch = 'o')

# immediately, large deviations are obvious, as well as some strikingly 
# non-linear and complex appearing relations between variables, most interestingly,
# the returns seem largely independent of all of these variables

# SECTION 2.2 --------------------------------------------------------------
# FITTING THE MODELS -------------------------------------------------------

# autoregressive stepwise model fitting 

# let's first fit our 11-term models
# the non-ransformed model
M0.10 <- lm(ret.AAPL ~ AAPL0 - 1 - Date, data = mdata10)
Mfull.10 <- lm(ret.AAPL ~ . - 1 - Date, data = mdata10)
Mstart.10 <- lm(ret.AAPL ~ AAPL0 + AAPL1 + VIX0 + BNDGLB0 + EEM0 - 1 - Date,
                data = mdata10)
Mstep.10 <- step(object = Mstart.10, scope = list(lower = M0.10, upper = Mfull.10),
                 direction = 'both', trace = FALSE)
# the scaled model
M0.10scl <- lm(ret.AAPL ~ AAPL0 - 1 - Date, data = mdata10scl)
Mfull.10scl <- lm(ret.AAPL ~ . - 1 - Date, data = mdata10scl)
Mstart.10scl <- lm(ret.AAPL ~ AAPL0 + AAPL1 + VIX0 + BNDGLB0 + EEM0 - 1 - Date,
                data = mdata10scl)
Mstep.10scl <- step(object = Mstart.10, scope = list(lower = M0.10, upper = Mfull.10scl),
                 direction = 'both', trace = FALSE)
# the log model
M0.10log <- lm(ret.AAPL ~ AAPL0 - 1 - Date, data = mdata10log)
Mfull.10log <- lm(ret.AAPL ~ . - 1 - Date, data = mdata10log)
Mstart.10log <- lm(ret.AAPL ~ AAPL0 + AAPL1 + VIX0 + BNDGLB0 + EEM0 - 1 - Date, 
                   data = mdata10log)
Mstep.10log <- step(object = Mstart.10log, scope = list(lower = M0.10log, upper = Mfull.10log),
                    direction = 'both', trace = FALSE)
# the log-scaled model
M0.10ls <- lm(ret.AAPL ~ AAPL0 - 1 - Date, data = mdata10ls)
Mfull.10ls <- lm(ret.AAPL ~ . - 1 - Date, data = mdata10ls)
Mstart.10ls <- lm(ret.AAPL ~ AAPL0 + AAPL1 + VIX0 + BNDGLB0 + EEM0 - 1 - Date,
                  data = mdata10ls)
Mstep.10ls <- step(object = Mstart.10ls, scope = list(lower = M0.10ls, upper = Mfull.10ls),
                   direction = 'both', trace = FALSE)

# now let's fit our 3-term models
# non-transformed model
M0.3int <- lm(ret.AAPL ~ AAPL0 - 1 - Date, data = mdata3)
Mfull.3int <- lm(ret.AAPL ~ (. - Date)^2 - 1, data = mdata3)
Mstart.3int <- lm(ret.AAPL ~ (. - BNDGLB0 - EEM1 - VIX2 - Date)^2 - 1, data = mdata3)
Mstep.3int <- step(object = Mstart.3int, scope = list(lower = M0.3int, upper = Mfull.3int),
                   direction = 'both', trace = FALSE)
# scaled model
M0.3intscl <- lm(ret.AAPL ~ AAPL0 - 1 - Date, data = mdata3scl)
Mfull.3intscl <- lm(ret.AAPL ~ (. - Date)^2 - 1, data = mdata3scl)
Mstart.3intscl <- lm(formula = form, data = mdata3scl)
Mstep.3intscl <- step(object = Mstart.3intscl, scope = list(lower = M0.3intscl, upper = Mfull.3intscl),
                      direction = 'both', trace = FALSE)
# log model
M0.3intlog <- lm(ret.AAPL ~ AAPL2 - 1 - Date, data = mdata3log)
Mfull.3intlog <- lm(ret.AAPL ~ (. - Date)^2 - 1, data = mdata3log)
Mstart.3intlog <- lm(formula = form, data = mdata3log)
Mstep.3intlog <- step(object = Mstart.3intlog, scope = list(lower = M0.3intlog, upper = Mfull.3intlog),
                      direction = 'both', trace = FALSE)
# log-scaled model
M0.3intls <- lm(ret.AAPL ~ AAPL0 - 1 - Date, data = mdata3ls)
Mfull.3intls <- lm(ret.AAPL ~ (. - Date)^2 - 1, data = mdata3ls)
Mstart.3intls <- lm(formula = form, data = mdata3ls)
Mstep.3intls <- step(object = Mstart.3intls, scope = list(lower = M0.3intls, upper = Mfull.3intls),
                     direction = 'both', trace = FALSE)

# now let's fit our 1-term models
# non-transformed
M0.1int <- lm(ret.AAPL ~ AAPL0 - 1 - Date, data = mdata1)
Mfull.1int <- lm(ret.AAPL ~ (. - Date)^2 - 1, data = mdata1)
Mstart.1int <- lm(ret.AAPL ~ (. - BNDGLB0 - EEM0 - VIX0 - Date)^2 - 1, data = mdata1)
Mstep.1int <- step(object = Mstart.1int, scope = list(lower = M0.1int, upper = Mfull.1int),
                   direction = 'both', trace = FALSE)
# scaled
M0.1intscl <- lm(ret.AAPL ~ AAPL0 - 1 - Date, data = mdata1scl)
Mfull.1intscl <- lm(ret.AAPL ~ (. - Date)^2 - 1, data = mdata1scl)
Mstart.1intscl <- lm(ret.AAPL ~ (. - BNDGLB0 - EEM0 - VIX0 - Date)^2 - 1, data = mdata1scl)
Mstep.1intscl <- step(object = Mstart.1intscl, scope = list(lower = M0.1intscl, upper = Mfull.1intscl),
                      direction = 'both', trace = FALSE)
# log
M0.1intlog <- lm(ret.AAPL ~ AAPL0 - 1 - Date, data = mdata1log)
Mfull.1intlog <- lm(ret.AAPL ~ (. - Date)^2 - 1, data = mdata1log)
Mstart.1intlog <- lm(ret.AAPL ~ (. - BNDGLB0 - EEM0 - VIX0 - Date)^2 - 1, data = mdata0log)
Mstep.1intlog <- step(object = Mstart.1intlog, scope = list(lower = M0.1intlog, upper = Mfull.1intlog),
                      direction = 'both', trace = FALSE)
# log-scaled
M0.1intls <- lm(ret.AAPL ~ AAPL0 - 1 - Date, data = mdata1ls)
Mfull.1intls <- lm(ret.AAPL ~ (. - Date)^2 - 1, data = mdata1ls)
Mstart.1intls <- lm(ret.AAPL ~ (. - BNDGLB0 - EEM0 - VIX0 - Date)^2 - 1, data = mdata1ls)
Mstep.1intls <- step(object = Mstart.1intls, scope = list(lower = M0.1intls, upper = Mfull.1intls),
                     direction = 'both', trace = FALSE)

# let's save our models
saveRDS(Mstep.10, 'M10')
saveRDS(Mstep.10log, 'M10log')
saveRDS(Mstep.10ls, 'M10ls')
saveRDS(Mstep.10scl, 'M10scl')

saveRDS(Mstep.3int, 'M3int')
saveRDS(Mstep.3intlog, 'M3intlog')
saveRDS(Mstep.3intls, 'M3intls')
saveRDS(Mstep.3intscl, 'M3intscl')

saveRDS(Mstep.1int, 'M1int')
saveRDS(Mstep.1intlog, 'M1intlog')
saveRDS(Mstep.1intls, 'M1intls')
saveRDS(Mstep.1intscl, 'M1intscl')


# simple analysis of preliminary models -------------------------------------

# This is helpful for examining our models, but figures are not in the report

# while all slopes included in this model are significant, the incredibly
# small values and very low value of R-squared for so many covariates
# indicates rather poor predictive and explanatory power
# let's plot the residuals
plot(Mstep.10$fitted, Mstep.10$resid)

# there are a few extreme residuals here, which seem to have an increasing 
# pattern, let's try adjusting by looking at the studentized residuals
# calculate hat matrix
H <- model.matrix(Mstep.10)
H <- H %*% solve(crossprod(H), t(H))
h <- diag(H)
res.stu <- Mstep.10$resid/sqrt(1-h) # studentized residuals
plot(Mstep.10$fitted, res.stu)
# let's also look at a normal comparison plot
sigma.hat <- sqrt(sum(Mstep.10$resid^2)/Mstep.10$df)
cex <- 0.8
par(mar = c(4,4,.1,.1), mfrow = c(1,1))
hist(res.stu/sigma.hat, breaks = 50, freq = FALSE, cex.axis = cex, main = '')
curve(dnorm(x), col = 'red', add = TRUE)

# here the residuals which were very extreme and seemed to show a pattern show,
# this plot gives rather normal results, but is very sharply peaked in the centre
# with much heavier tails, this indicates the our data is, for the most part, close
# to our lines, but there is a significant density in the tails, as well, given
# that our residuals seemed to be further away from the line at the tails, we
# have indications of heteroscedastic effects

# while all slopes included in this model are significant, the incredibly
# small values and very low value of R-squared for so many covariates
# indicates rather poor predictive and explanatory power
# let's plot the residuals
plot(Mstep.10$fitted, Mstep.10$resid)

# there are a few extreme residuals here, which seem to have an increasing 
# pattern, let's try adjusting by looking at the studentized residuals
# calculate hat matrix
H <- model.matrix(Mstep.10)
H <- H %*% solve(crossprod(H), t(H))
h <- diag(H)
res.stu <- Mstep.10$resid/sqrt(1-h) # studentized residuals
plot(Mstep.10$fitted, res.stu)
# let's also look at a normal comparison plot
sigma.hat <- sqrt(sum(Mstep.10$resid^2)/Mstep.10$df)
cex <- 0.8
par(mar = c(4,4,.1,.1), mfrow = c(1,1))
hist(res.stu/sigma.hat, breaks = 50, freq = FALSE, cex.axis = cex, main = '')
curve(dnorm(x), col = 'red', add = TRUE)

# here the residuals which were very extreme and seemed to show a pattern show,
# this plot gives rather normal results, but is very sharply peaked in the centre
# with much heavier tails, this indicates the our data is, for the most part, close
# to our lines, but there is a significant density in the tails, as well, given
# that our residuals seemed to be further away from the line at the tails, we
# have indications of heteroscedastic effects

# 3-term model
# some of the included terms were not significant, remove these terms to make 
# a comparison model
inds <- summary(Mstep.3int)$coefficients[,4] < 0.1
covs <- rownames(summary(Mstep.3int)$coefficients)[inds]
form <- as.formula(paste('ret.AAPL', 
                         paste('AAPL0', covs, collapse = ' + ', sep = ' + '), sep = ' ~ '))
Mstep.3int2 <- lm(form, data = mdata3)

# now let's do an F-test to see how significant removing all of these terms actually
# was, we are tesing the hypothesis they are all zero vs the hypothesis they are not
# results are in the report
anova(Mstep.3int2, Mstep.3int)


# SECTION 2.2 --------------------------------------------------------------
# Analysis of AIC and PRESS used in report ---------------------------------

# Load models we discussed before
# Here are the naming conventions going forward

M1int <- readRDS(file.choose()) # 1 day w/interactions
M1intlog <- readRDS(file.choose()) # 1 day w/interactions, log transformed
M1intscl <- readRDS(file.choose()) # 1 day w/interactions, scaled for volatility
M1intls <- readRDS(file.choose()) # 1 day w/interactions, log transformed and scaled

M3int <- readRDS(file.choose()) # 3 day w/interactions
M3intlog <- readRDS(file.choose()) # 3 day w/interactions, log transformed
M3intscl <- readRDS(file.choose()) # 3 day w/interactions, scaled
M3intls <- readRDS(file.choose()) # 3 day w/interactions, log transformed and scaled

M10 <- readRDS(file.choose()) # 10 day 
M10log <- readRDS(file.choose()) # 10 day, log transformed
M10scl <- readRDS(file.choose()) # 10 day, scaled
M10ls <- readRDS(file.choose()) # 10 day, log transformed and scaled


# SECTION 2.2 --------------------------------------------------------------
# AIC  ---------------------------------------------------------------------

# Used to filter out some of the 12 models

# let's look at the Akaike Information Criterion for these models
AIC.M11 <- AIC(M1int)
AIC.M12 <- AIC(M1intlog)
AIC.M13 <- AIC(M1intscl)
AIC.M14 <- AIC(M1intls)
AIC.M31 <- AIC(M3int)
AIC.M32 <- AIC(M3intlog)
AIC.M33 <- AIC(M3intscl)
AIC.M34 <- AIC(M3intls)
AIC.M101 <- AIC(M10)
AIC.M102 <- AIC(M10log)
AIC.M103 <- AIC(M10scl)
AIC.M104 <- AIC(M10ls)

# Names of our models, useful for future plots
M1names<-expression(M1int, M1intlog, M1intscl, M1intls)
M3names<-expression(M3int, M3intlog, M3intscl, M3intls)
M10names<-expression(M10, M10log, M10scl, M10ls)
Mnames <- c(M1names,M3names,M10names)

M1.AICs <- c(AIC.M1int = AIC.M11, AIC.M1intlog = AIC.M12, 
             AIC.M1intscl = AIC.M13, AIC.M1intls = AIC.M14)
M3.AICs <- c(AIC.M3int = AIC.M31, AIC.M3intlog = AIC.M32, 
             AIC.M3intscl = AIC.M33, AIC.M3intls = AIC.M34)
M10.AICs <- c(AIC.M0int = AIC.M101, AIC.M10intlog = AIC.M102, 
             AIC.M10intscl = AIC.M103, AIC.M10intls = AIC.M104)

# Results are in the AIC/PRESS table
AICs <- c(M1.AICs,M3.AICs,M10.AICs)
AICs

# AIC values are clearly poorer for the data which has not been scaled
# Scaling for volatility better captures the relation in the model
# As a result, the PRESS statistics of each of the six scaled models was plotted

# SECTION 2.2 --------------------------------------------------------------
# PRESS  -------------------------------------------------------------------

# let's look at the PRESS statistics for these models -- M1 (1-day)
pres1<-resid(M1int)/(1-hatvalues(M1int))# M1
pres2<-resid(M1intlog)/(1-hatvalues(M1intlog))# M2
pres3<-resid(M1intscl)/(1-hatvalues(M1intscl))# M3
pres4<-resid(M1intls)/(1-hatvalues(M1intls))# M4
P1<- c(PRESS1 = sum(pres1^2), PRESS2 = sum(pres2^2), 
  PRESS3 = sum(pres3^2), PRESS4 = sum(pres4^2))

# let's look at the PRESS statistics for these models -- M3 (3-day)

press1<-resid(M3int)/(1-hatvalues(M3int))# M1
press2<-resid(M3intlog)/(1-hatvalues(M3intlog))# M2
press3<-resid(M3intscl)/(1-hatvalues(M3intscl))# M3
press4<-resid(M3intls)/(1-hatvalues(M3intls))# M4
P3<- c(PRESS1 = sum(press1^2), PRESS2 = sum(press2^2), 
  PRESS3 = sum(press3^2), PRESS4 = sum(press4^2))


# let's look at the PRESS statistics for these models -- M10 (10-day)
press.1<-resid(M10)/(1-hatvalues(M10))# M1
press.2<-resid(M10log)/(1-hatvalues(M10log))# M2
press.3<-resid(M10scl)/(1-hatvalues(M10scl))# M3
press.4<-resid(M10ls)/(1-hatvalues(M10ls))# M4
P10<-c(PRESS1 = sum(press.1^2), PRESS2 = sum(press.2^2), 
  PRESS3 = sum(press.3^2), PRESS4 = sum(press.4^2))

# Results are in the AIC/PRESS table
AllPress<- c(P1,P3,P10)
AllPress

# plot PRESS for M1, M3 and M10 with scale and log&scale 
# (models we chose according to AIC)
# FIGURE 2 
boxplot(x = list(pres3^2,pres4^2,press3^2,press4^2,press.3^2,press.4^2), 
        names = expression(M1intscl,M1intls,M3intscl, M3intls,M10scl, M10ls),
        ylab = expression(PRESS[i]^2), 
        col = c("red","orange","yellow","green","blue","purple"),
        ylim = c(0.0000, 0.000075))

# Tthree day scaled model with interaction effects clearly 
# has the best PRESS statistic characteristics.
# The distribution of its PRESS2 residuals is notably lower than the other models.
# There is no clear second best model.

# plot PRESS statistics for ALL models for Appendix
# FIGURE A2 
boxplot(x = list(pres1^2, pres2^2,pres3^2,pres4^2,
  pres1^2, press2^2,press3^2,press4^2,
  press.1^2, press.2^2,press.3^2,press.4^2),
        names = c(Mnames),ylab = expression(PRESS[i]^2), 
        col = c("yellow","orange","red","blue","purple","green",
          "grey","brown","white","maroon","pink","violet"),
        ylim = c(-0.00003, 0.03))


# SECTION 2.3: MODEL DIAGNOSTICS ------------------------------------------

# we're going to use the scaled model with 1 day and 3 days
# justification can be found in the report 
# the PRESS statistic tells us that scaling makes a big difference 
# the AIC tells us that taking the log helps preserve information

# rename models to simple names 
N1<-M1intscl # 1-day model with interactions, scaled for volatility
N2<-M3intscl # 3-day model with interactions, scaled for volatility

# SECTION 2.3 --------------------------------------------------------------
# RESIDUAL PLOTS -----------------------------------------------------------

# For both models, the studentized residuals and DFFITS residuals were plotted. 
# Reasons for the choice of these two particular residual measures:
# - studentized residuals are the most normal residuals if the 
#   model assumptions are correct 
# - the DFFITS residual highlights outliers most clearly. 


# RESIDUAL PLOTS, 1-DAY MODEL ----------------------------------------------
Msum<- summary(N1)
# residuals vs predicted values
y.hat <- predict(N1) # predicted values
sigma.hat <- Msum$sigma
res <- resid(N1) # original residuals
stan.res <- res/sigma.hat # standardized residuals
# compute leverages
X <- model.matrix(N1)
H <- X %*% solve(crossprod(X), t(X)) # HAT matrix
head(diag(H))
h <- hatvalues(N1) # the R way
range(h - diag(H))
# studentized residuals
stud.res <- stan.res/sqrt(1-h)
# DFFITS residuals
dfts <- dffits(N1) # the R way

# standardize each of these such that they are identical at the average leverage value
p <- length(coef(N1))
n <- nobs(N1)
hbar <- p/n # average leverage
stud.res <- stud.res*sqrt(1-hbar) # at h = hbar, stud.res = stan.res
dfts <- dfts*(1-hbar)/sqrt(hbar) # at h = hbar, dfts = stan.res

# plot all residuals
par(mfrow = c(1,2), mar = c(4,4,.1,.1))
# against predicted values
cex <- .8
plot(y.hat, rep(0, length(y.hat)), type = "n", # empty plot to get the axis range
     ylim = range(stan.res, stud.res, press, dfts), cex.axis = cex,
     xlab = "Predicted Values", ylab = "Residuals")

# dotted line connecting each observations residuals for better visibility
segments(x0 = y.hat,
         y0 = pmin(stud.res, dfts),
         y1 = pmax(stud.res,dfts),
         lty = 2)
# plot points
points(y.hat, stud.res, pch = 21, bg = "blue", cex = cex)
points(y.hat, dfts, pch = 21, bg = "red", cex = cex)

# against leverages
plot(h, rep(0, length(y.hat)), type = "n", cex.axis = cex,
     ylim = range(stud.res, dfts),
     xlab = "Leverages", ylab = "Residuals")
segments(x0 = h,
         y0 = pmin(stud.res, dfts),
         y1 = pmax( stud.res,dfts),
         lty = 2)
points(h, stud.res, pch = 21, bg = "blue", cex = cex)
points(h, dfts, pch = 21, bg = "red", cex = cex)
abline(v = hbar, col = "grey60", lty = 2)

# create legend
legend("topright", legend = c("Studentized", "DFFITS"),
       pch = 21, pt.bg = c("blue", "red"), title = "Residual Type:",
       cex = cex, pt.cex = cex)


# RESIDUAL PLOTS, 3-DAY MODEL --------------------------------------------

Msum<- summary(N2)
# residuals vs predicted values
y.hat <- predict(N2) # predicted values
sigma.hat <- Msum$sigma
res <- resid(N2) # original residuals$
stan.res <- res/sigma.hat # standardized residuals
# compute leverages
X <- model.matrix(N2)
X
H <- X %*% solve(crossprod(X), t(X)) # HAT matrix
head(diag(H))
h <- hatvalues(N2) # the R way
range(h - diag(H))
# studentized residuals
stud.res <- stan.res/sqrt(1-h)
# DFFITS residuals
dfts <- dffits(N2) # the R way

# standardize each of these such that they are identical at the average leverage value
p <- length(coef(N2))
n <- nobs(N2)
hbar <- p/n # average leverage
stud.res <- stud.res*sqrt(1-hbar) # at h = hbar, stud.res = stan.res
dfts <- dfts*(1-hbar)/sqrt(hbar) # at h = hbar, dfts = stan.res

# plot all residuals
par(mfrow = c(1,2), mar = c(4,4,.1,.1))
# against predicted values
cex <- .8
plot(y.hat, rep(0, length(y.hat)), type = "n", # empty plot to get the axis range
     ylim = range(stan.res, stud.res, press, dfts), cex.axis = cex,
     xlab = "Predicted Values", ylab = "Residuals")

# dotted line connecting each observations residuals for better visibility
segments(x0 = y.hat,
         y0 = pmin(stud.res, dfts),
         y1 = pmax(stud.res,dfts),
         lty = 2)
# plot points
points(y.hat, stud.res, pch = 21, bg = "blue", cex = cex)
points(y.hat, dfts, pch = 21, bg = "red", cex = cex)

# against leverages
plot(h, rep(0, length(y.hat)), type = "n", cex.axis = cex,
     ylim = range(stud.res, dfts),
     xlab = "Leverages", ylab = "Residuals")
segments(x0 = h,
         y0 = pmin(stud.res, dfts),
         y1 = pmax( stud.res,dfts),
         lty = 2)
points(h, stud.res, pch = 21, bg = "blue", cex = cex)
points(h, dfts, pch = 21, bg = "red", cex = cex)
abline(v = hbar, col = "grey60", lty = 2)
# add legend
legend("topright", legend = c("Studentized", "DFFITS"),
       pch = 21, pt.bg = c("blue", "red"), title = "Residual Type:",
       cex = cex, pt.cex = cex)


# SECTION 2.3 --------------------------------------------------------------
# LEVERAGE AND INFLUENCE PLOTS ---------------------------------------------

# Leverages and Cook Distances , 1-DAY MODEL -------------------------------
D <- cooks.distance(N1)
# flag some of the points
infl.ind <- which.max(D) # top influence point
lev.ind <- h > 2*hbar # leverage more than 2x the average
clrs <- rep("black", len = n)
clrs[lev.ind] <- "blue"
clrs[infl.ind] <- "red"
par(mfrow = c(1,1), mar = c(4,4,1,1))
cex <- .8
plot(h, D, xlab = "Leverage", ylab = "Cook’s Influence Measure",
     pch = 21, bg = clrs, cex = cex, cex.axis = cex)
p <- length(coef(N1))
n <- nrow(market)
hbar <- p/n # average leverage
abline(v = 2*hbar, col = "grey60", lty = 2) # 2x average leverage
legend("topleft", legend = c("High Leverage", "High Influence"), pch = 21,
       pt.bg = c("blue", "red"), cex = cex, pt.cex = cex)

# Roughly a third of the observations have twice the average leverage or more. 
# There are simply too many points to remove without compromising the integrity of the data 


# Leverages and Cook Distances , 3-DAY MODEL --------------------------------
D <- cooks.distance(N2)
# flag some of the points
infl.ind <- which.max(D) # top influence point
lev.ind <- h > 4*hbar # leverage more than 2x the average
clrs <- rep("black", len = n)
clrs[lev.ind] <- "blue"
clrs[infl.ind] <- "red"
par(mfrow = c(1,1), mar = c(4,4,1,1))
cex <- .8
plot(h, D, xlab = "Leverage", ylab = "Cook’s Influence Measure",
     pch = 21, bg = clrs, cex = cex, cex.axis = cex)
p <- length(coef(N2))
n <- nrow(log(market))
hbar <- p/n # average leverage
abline(v = 2*hbar, col = "grey60", lty = 2) # 2x average leverage
legend("topleft", legend = c("High Leverage", "High Influence"), pch = 21,
       pt.bg = c("blue", "red"), cex = cex, pt.cex = cex)

# Same as 1-day model
# Roughly a third of the observations have twice the average leverage or more. 
# There are simply too many points to remove without compromising the integrity of the data 


# SECTION 2.3 --------------------------------------------------------------
# CROSS VALIDATION ---------------------------------------------------------

# gather lambda and sum of squared errors for the best models as determined by
# AIC in the analysis code
# 3 days with interactions scaled
# 1 day interactions scaled
# chosen because they are, respectively, the fastest to compute and most readily 
# interpretable and the best fitting model by AIC and PRESS statistic values
nreps <- 2e3
ntot1 <- nrow(mdata3scl)
ntot2 <- nrow(mdata1scl)
ntrain <- 2500
ntest1 <- ntot1 - ntrain
ntest2 <- ntot2 - ntrain
sse3t <- rep(NA, nreps)
sse1t <- rep(NA, nreps)
Lambda <- rep(NA, nreps)

for (ii in 1:nreps) {
  if (ii%%100 == 0) message("ii = ", ii)
  tr.ind1 <- sample(ntot1, ntrain)
  tr.ind2 <- sample(ntot2, ntrain)
  M3t.cv <- update(M3intscl, subset = tr.ind1)
  M1t.cv <- update(M1intscl, subset = tr.ind2)
  M3tres <- mdata3$ret.AAPL[-tr.ind1] - (mdata3$VIX0[-tr.ind1]^0.5)*
  predict(M3t.cv, newdata = mdata3scl[-tr.ind1,])
  M1tres <- mdata1$ret.AAPL[-tr.ind2] - (mdata1$VIX0[-tr.ind2]^0.5)*
  predict(M1t.cv, newdata = mdata1scl[-tr.ind2,])
  sse3t[ii] <- sum((M3tres)^2)
  sse1t[ii] <- sum((M1tres)^2)
  M3t.sigma <- sqrt(sum((mdata3$VIX0[tr.ind1])^(1/2)*resid(M3t.cv)^2)/ntrain)
  M1t.sigma <- sqrt(sum((mdata1$VIX0[tr.ind2])^(1/2)*resid(M1t.cv)^2)/ntrain)
  Lambda[ii] <- sum(dnorm(M3tres, mean = 0, sd = M3t.sigma, log = TRUE))
  Lambda[ii] <- Lambda[ii] - sum(dnorm(M1tres, mean = 0, sd = M1t.sigma, log = TRUE))
}

# plot points
# plot cross-validation SSE and Lambda
Mnames <- expression(M['3term'], M['1term'])
par(mfrow = c(1,2))
par(mar = c(4.5, 4.5, .1, .1))
boxplot(x = list(sse3t, sse1t), names = Mnames, cex = .7,
        ylab = expression(SS[err]^{test}), col = c("yellow", "orange"))
hist(Lambda, breaks = 50, freq = FALSE, xlab = expression(Lambda^{test}),
     main = "", cex = .7)
abline(v = mean(Lambda), col = "red") # average value

# residual plots
par(mfrow = c(1,1))
plot(dates[3:(length(dates) - 1)], M3intscl$resid)
plot(dates[3:(length(dates)-1)], mdata3scl$ret.AAPL)
plot(dates[1:(length(dates) - 1)], M1intscl$resid)
plot(dates[1:(length(dates)-1)], mdata1scl$ret.AAPL)

# intervals for significant coefficients
# extract significant coefficients at level 0.05
inds <- coef(summary(M3intscl))[,4] < 0.05
sigcoef <- coef(summary(M3intscl))[inds,]
# let's see if the insignificant slopes are truly zero
redf <- as.formula(paste('ret.AAPL', 
                         paste(paste(rownames(sigcoef),
                               collapse = ' + '), 1, sep = ' - '), sep = ' ~ '))
fullfnoint <- as.formula(paste('ret.AAPL',
                          paste(paste(rownames(coef(summary(M3intscl)))[2:length(inds)],
                                collapse = ' + '), '1', sep = ' - '), sep = ' ~ '))
# create a reduced model
redmod <- lm(formula = redf, data = mdata3scl)
# anova on models
anova(redmod, M3intscl)
# so we have significant evidence that these coefficients are not equal to zero
# as we gain a p-value of 0.00047, as a result we should leave them in the model
# However, it is important to note this indicates these values are strongly
# correlated, let's look at VIF values for these indices

# SECTION 2.3 --------------------------------------------------------------
# VARIANCE INFLATION FACTORS -----------------------------------------------

# Under "Parameter Estimates and Confidence Intervals"

X <- model.matrix(lm(fullfnoint, data = mdata3scl))
VIF3 <- diag(solve(cor(X)))
# Clearly, our model includes terms which are very highly correlated. 
# This explains why we have so many insignificant terms included.

Xred <- model.matrix(lm(redf, data = mdata3scl))
redVIF <- diag(solve(cor(Xred)))

# what about the VIF for the other model? (JUST FOR CURIOUSITY, NOT IN REPORT)
Y <- model.matrix(M1intscl)
VIF1 <- diag(solve(cor(Y)))

