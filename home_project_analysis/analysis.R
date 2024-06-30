# Quantitative Finance: CPP2
# Adam Foster
# University of Warsaw
# 2024-06-30

library(gridExtra)
library(tibble)
library(dplyr)
library(plotly)

# Remove package if it exists
remove.packages("OptionPricer")
detach("package:OptionPricer", unload = TRUE)

# Install package and load to memory - ensure package path is correct
install.packages("../OptionPricer_0.1.0.tar.gz",
                 type = "source",
                 repos = NULL)

library("OptionPricer")

# Call the function using the parameters provided
priceStart <- MCAsianBarrierPortfolioPricer(5.0 / 12.0, 115, 0.25, 0.05, 0.0, 1000000, 126, 0.8 * 115)
priceStart

# Price the portfolio under multiple combinations of spot prices and barriers
MCAsianBarrierPortfolioPricerWrapper <- function(spot, barrier) {
  return(MCAsianBarrierPortfolioPricer(5.0 / 12.0, spot, 0.25, 0.05, 0.0, 1000000, 126, barrier))
}

spots <- seq(100, 130, by = 5) # equidistant range around current spot
barriers <- seq(85, 115, by = 5) # several possibilities up to spot

outSize <- length(spots) * length(barriers)
spotOut <- numeric(outSize)
barrierOut <- numeric(outSize)
priceOut <- numeric(outSize)

i <- 1
for (spot in spots) {
  for (barrier in barriers) {
    spotOut[i] <- spot
    barrierOut[i] <- barrier
    priceOut[i] <- MCAsianBarrierPortfolioPricerWrapper(spot, barrier)

    cat(paste("Finished pricing ", i, "/", outSize, " portfolios\n"))
    i <- i + 1
  }
}

spotOut[23]
barrierOut[23]
priceOut[23] # verify price based on similar parameters is close starting price calculated earlier

# Visualise portfolio prices under the multiple spot-barrier combinations
priceMatrix <- matrix(priceOut, nrow = length(barriers), ncol = length(spots), byrow = TRUE)

axx <- list(
  title = "Spot"
)

axy <- list(
  title = "Barrier"
)

axz <- list(
  title = "Price"
)

priceFig <- plot_ly(
  x = ~spots,
  y = ~barriers,
  z = ~t(priceMatrix),
  type = "surface",
  colorscale = 'Viridis',
  colorbar = list(title = "Price")
)

priceFig <- priceFig %>% layout(scene = list(xaxis = axx, yaxis = axy, zaxis = axz))
priceFig
